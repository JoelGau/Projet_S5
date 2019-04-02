%% Test_EZWEED
% Programmeurs:             JG,
% Date de création:         2019-03-23
% Dernière modification:    2019-03-30
% Description:              
% Ce script sert à tester la fonctionnalité de getEZWEED.m, teachEZWEED.m
% Il comprend aussi une section pour identifier les composantes
% essentielles du mot.
%% Teaching
load('ez.mat');
sound(x_16, 16000);
%% Testing getEZWEED.m
clc
clear all
close all

myVoice = audiorecorder(16000,16,1);
% Define callbacks to show when
% recording starts and completes.
myVoice.StartFcn = 'disp(''Start speaking.'')';
myVoice.StopFcn = 'disp(''End of recording.'')';
recordblocking(myVoice, 5);

x_16 = getaudiodata(myVoice, 'double');
F0 = 23;

getEZWEED(x_16,F0);
%sound(x_16,16000)
%% Testing teachEZWEED.m
clc
clear all
close all

myVoice = audiorecorder(16000,16,1);
% Define callbacks to show when
% recording starts and completes.
myVoice.StartFcn = 'disp(''Start speaking.'')';
myVoice.StopFcn = 'disp(''End of recording.'')';
recordblocking(myVoice, 5);
x_16 = getaudiodata(myVoice, 'double');

% Déterminer la fréquence fondamentale de l'enregistrement
F0 = teachEZWEED(x_16,16000);
%% Testing getF0.m
clc
clear all
close all

LONGUEUR_TRAME = 1024;
n = 1:1:LONGUEUR_TRAME;
f = 111;
fe = 16000;

x_n = sin(2.*pi.*f./fe*n);

autocorr = CorrelationCroisee(x_n,x_n);

F0 = getF0(autocorr,LONGUEUR_TRAME,16000);

%% Old stuff
%% Enregistrment de "EZWEED"
clc
clear all
close all

% Fenetrage hamming
LONGUEUR_TRAME = 1024;
F_hm = hamming(LONGUEUR_TRAME);

% Enregistrement audio
myVoice = audiorecorder(16000,16,1);
myVoice.StartFcn = 'disp(''Start speaking.'')';
myVoice.StopFcn = 'disp(''End of recording.'')';
recordblocking(myVoice, 5);
x_16 = getaudiodata(myVoice, 'double');
%% Isoler les fréquences pertinentes
% Aller chercher l'information importante
figure(1)
plot(x_16)
[pointx,pointy] = getpts;
pointx = round(pointx);
close figure 1

% Isoler la FFT
x_my = x_16(pointx:pointx+LONGUEUR_TRAME-1).*F_hm;
X_my = fft(x_my);

figure(1)
plot(abs(X_my))