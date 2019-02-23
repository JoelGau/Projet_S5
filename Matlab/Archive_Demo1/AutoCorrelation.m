%% AutoCorrelation
% Programmeurs:             JG,
% Date de création:         2019-02-23
% Dernière modification:    2019-02-23
% Description:              
% Le but de cette fonction est de faire l'autocorrelation d'un signal de
% référence avec un signal d'entrée. On doit être en mesure de juger de la
% ressemblance des 2 signaux.
%% Core
clc
clear all
close all
x1 = [1 1 0];
x2 = [1 0 1 1];

%[x,fe] = audioread('Tropical_JG_2019-02-23_09-33-49.wav');

y = xcorr(x1,x2);
y2 = CorrelationCroisee(x1,x2);
