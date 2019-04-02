%% SignalRef
% Programmeurs:             JG,
% Date de création:         2019-03-17
% Dernière modification:    2019-03-18
% Description:              
% Ce sript sert à déterminer le signal de référence pour la comparaison des
% échantillons qui sont rentrés dans l'algorithme.
%% Core
clc
clear all
close all

% Récupérer les données
EAD = load('EAD_Tropical');
JG1 = load('JG1_Tropical');
JG2 = load('JG2_Tropical');
JL = load('JL_Tropical');
MSP = load('MSP_Tropical');
SV = load('SV_Tropical');

% Test pour comparaison signaux
% y = xcorr(abs(EAD.X_FFT(:,1)),abs(JG2.X_FFT(:,1)));

%