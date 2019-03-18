%% SignalRef
% Programmeurs:             JG,
% Date de cr�ation:         2019-03-17
% Derni�re modification:    2019-03-18
% Description:              
% Ce sript sert � d�terminer le signal de r�f�rence pour la comparaison des
% �chantillons qui sont rentr�s dans l'algorithme.
%% Core
clc
clear all
close all

% R�cup�rer les donn�es
EAD = load('EAD_Tropical');
JG1 = load('JG1_Tropical');
JG2 = load('JG2_Tropical');
JL = load('JL_Tropical');
MSP = load('MSP_Tropical');
SV = load('SV_Tropical');

% Test pour comparaison signaux
% y = xcorr(abs(EAD.X_FFT(:,1)),abs(JG2.X_FFT(:,1)));

%