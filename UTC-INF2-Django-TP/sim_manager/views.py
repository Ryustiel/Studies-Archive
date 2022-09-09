from django.contrib import auth
from django.shortcuts import render, get_object_or_404
from django.forms.models import model_to_dict
from .models import Simulation
from .forms import UserProfileForm, SimuForm, RegisterForm, PasswordCheckForm #ADDON
from django.contrib.auth.forms import PasswordChangeForm, AuthenticationForm #ADDON
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib.auth import logout, authenticate, login #ADDON
from django.http import HttpResponseRedirect
from django.urls import reverse_lazy
from pyfhn.fhn_runner import run_fhn_base
import matplotlib.pyplot as plt
from io import StringIO


# Create your views here.
def landing(request):
    return render(request, "base.html", locals())


@login_required(login_url="/login/") #Shortened
def simulation_list(request):
    simulations = Simulation.objects.filter(user=request.user)

    return render(request, "simulation_list.html", {"user_sims": simulations})

#================================================================================================================= CUSTOM VIEWS

def login_view(request): #ADDON
    if request.method == "POST":
        login_form = AuthenticationForm(request, data=request.POST)

        if login_form.is_valid():
            user_cache = authenticate(username=login_form.cleaned_data.get("username"), password=login_form.cleaned_data.get("password"))

            if user_cache is not None:
                login(request, user_cache)
                return HttpResponseRedirect("/")

        return render(request, "registration/login.html", {'form': login_form, 'message': "You typed a wrong username or password"})

    else:
        try: #parameter handeling
            switch = request.GET['reason']

            if switch == 'logout':
                message = "You logged out"
            elif switch == 'register':
                message = "Your have registered successfully. You may now login"
            elif switch == 'password':
                message = "Your password has been changed successfully"
            elif switch == 'deleted':
                message = "Your account has been deleted. You could login with another account or Register"
            else:
                message = ''
        except:
            message = ''

        login_form = AuthenticationForm(request)
        return render(request, "registration/login.html", {'form': login_form, 'message': message})

def liste_inscrits(request): #ADDON
    user_list = User.objects.all() #recup database
    return render(request, "liste_inscrits.html", {'user_list': user_list})

def register(request): #ADDON
    envoi = False
    if request.method == "POST":
        register_form = RegisterForm(request.POST)
        if register_form.is_valid():
            register_form.save() #saves to User ORM
            return HttpResponseRedirect("/login?reason=register") #REGISTER CONFIRM MESSAGE
        return render(request, "registration/register.html", {'form': register_form, 'message':"incorrect data"})
    else:
        register_form = RegisterForm()
    return render(request, "registration/register.html", {'form': register_form, 'message':""})

@login_required(login_url="/login/") #ADDON
def change_password(request):
    if request.method == "POST":
        password_form = PasswordChangeForm(request.user, data=request.POST) #automatically compares post data to the database
        if password_form.is_valid():
            password_form.save() #updates password
            return HttpResponseRedirect("/login?reason=password") #user has to login again
        return render(request, "account/password_change.html", {'form':password_form, 'message':"the old password or the new passwords do not match"})
    else:
        password_form = PasswordChangeForm(request.user)
        return render(request, "account/password_change.html", {'form':password_form, 'message':""})

@login_required(login_url="/login/") #ADDON
def account_deletion(request): 
    if request.method == "POST":
        check_form = PasswordCheckForm(request.POST)
        if check_form.is_valid():
            password = check_form.cleaned_data['password']
            if request.user.check_password(password): #login required
                u = User.objects.get(username = request.user.username) #user deletion
                u.delete()
                return HttpResponseRedirect("/login?reason=deleted")
        return render(request, "account/account_deletion.html", {'form':check_form, 'message':"invalid password"})
    else:
        check_form = PasswordCheckForm()
        return render(request, "account/account_deletion.html", {'form':check_form, 'message':""})

def logout_view(request): #ADDON
    logout(request)
    return HttpResponseRedirect("/login?reason=logout")

#=================================================================================================================

@login_required(login_url="/login/")
def edit_profile(request):
    envoi = False
    if request.method == "POST":
        user_profile_form = UserProfileForm(request.POST)
        if user_profile_form.is_valid() and user_profile_form.cleaned_data["email"]:
            current_user = User.objects.get(username=request.user.username)
            current_user.first_name = user_profile_form.cleaned_data["first_name"]
            current_user.last_name = user_profile_form.cleaned_data["last_name"]
            current_user.email = user_profile_form.cleaned_data["email"]
            current_user.save()
    else:
        user_profile_form = UserProfileForm(instance=request.user)
    return render(request, "account/edit_profile.html", {"form": user_profile_form}) #ADDON Coherence


@login_required(login_url="/login/")
def new_simu(request):
    # Construire le formulaire, soit avec les données postées,
    # soit vide si l'utilisateur accède pour la première fois
    # à la page.
    form = SimuForm(request.POST, request.FILES)
    if form.is_valid():

        params = form.cleaned_data
        print(params)
        newsim = Simulation(
            user=params["user"],
            alpha=params["alpha"],
            beta=params["beta"],
            gamma=params["gamma"],
            delta=params["delta"],
            epsilon=params["epsilon"],
        )
        newsim.save()
        return run_sim(request, newsim.id)
    return render(request, "newsimu.html", locals())


def run_sim(request, object_id):
    params = model_to_dict(get_object_or_404(Simulation, pk=object_id))
    params.pop("user")
    params.pop("id")
    res = run_fhn_base(params)
    f = plt.figure()
    plt.title("FHN Simulation")
    plt.xlabel("Time")
    plt.ylabel("Outputs")
    plot = plt.plot(res["t"], res["y"][0], res["t"], res["y"][1])
    plt.legend(["v", "w"])
    imgdata = StringIO()
    f.savefig(imgdata, format="svg")
    imgdata.seek(0)

    data = imgdata.getvalue()
    return render(request, "graphic.html", {"graphic": data})


@login_required(login_url="/login/")
def simulation_delete(request, object_id):
    sim = get_object_or_404(Simulation, pk=object_id)
    sim.delete()
    return HttpResponseRedirect(reverse_lazy("sim_list"))
