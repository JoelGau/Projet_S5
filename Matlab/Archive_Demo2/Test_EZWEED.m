%% Test_EZWEED
% Programmeurs:             JG,
% Date de création:         2019-03-23
% Dernière modification:    2019-03-24
% Description:              
% Ce script sert à tester la fonctionnalité de getEZWEED.m
% Il comprend aussi une section pour identifier les composantes
% essentielles du mot.
%% Testing
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

getEZWEED(x_16,16000)
sound(x_16,16000)
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

%% Isoler
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