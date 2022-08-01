from django.db import models
from django.contrib.auth.models import User
from django.core.validators import MaxValueValidator, MinValueValidator


# Create your models here.
class Simulation(models.Model):
    user = models.ForeignKey(User, on_delete=models.PROTECT)
    date = models.DateTimeField(auto_now_add=True, auto_now=False)
    alpha = models.FloatField(validators=[MinValueValidator(0.08), MaxValueValidator(0.12)],)
    beta = models.FloatField(validators=[MinValueValidator(0.4), MaxValueValidator(0.6)],)
    gamma = models.FloatField(validators=[MinValueValidator(0.04), MaxValueValidator(0.06)],)
    delta = models.FloatField(validators=[MinValueValidator(0.008), MaxValueValidator(0.012)],)
    epsilon = models.FloatField(validators=[MinValueValidator(0.08), MaxValueValidator(0.12)],)
