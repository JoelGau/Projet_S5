%% TrameDef
% Programmeurs:             JG,LPBR
% Date de création:         2019-02-25
% Dernière modification:    2019-02-25
% Description:              
% Le script suivant sert à déterminer la longueur d'une trame lors d'un
% enregistrement. Pour ce faire, on prend notre échantillon de son, on fait
% sa FFT et on isole la fréquence utile la plus basse à l'intérieur. Par la
% suite, on est en mesure de retrouver la période la plus longue de notre
% signal. La trame sera d'une longueur de cette péridode x2.
%% Core
clc
clear all
close all

%On load le signal de référence
[y,Fs] = audioread('SonGraveO.wav');
T = 1/Fs;
L = length(y);
t = (0:L-1)*T;
w = hamming(L);
Y = y.*w; %Fenêtrage

FFT = fft(Y);
P2 = abs(FFT/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
P = 20*log10(P1/max(abs(P1)));
f = Fs*(0:(L/2))/L;

% Affichage FFT du signal d'origine
figure(1)
semilogx(f(2:end-1),P(2:end-1))
grid
xlabel('Frequency (Hz)')
ylabel('Amplitude (dB)')
title('LA d origine')

% Selon le graph, la freq min est à 106 Hz environ
% tmin = 20 ms