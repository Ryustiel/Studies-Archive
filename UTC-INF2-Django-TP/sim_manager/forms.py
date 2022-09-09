from django import forms
from .models import Simulation
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm


class SimuForm(forms.ModelForm):
    class Meta:
        model = Simulation
        fields = '__all__'


class UserProfileForm(forms.ModelForm):
    class Meta:
        model = User
        fields = ['first_name', 'last_name', 'email']

class RegisterForm(UserCreationForm): #ADDON
    first_name = forms.CharField(max_length=100)
    last_name = forms.CharField(max_length=100)
    email = forms.CharField(max_length=100)
    class Meta:
        model = User 
        fields = ['username', 'first_name', 'last_name', 'email', 'password1', 'password2']

class PasswordCheckForm(forms.ModelForm):
    password = forms.CharField(max_length=100, widget=forms.PasswordInput())
    class Meta:
        model = User 
        fields = ['password']
