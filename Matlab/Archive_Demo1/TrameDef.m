%% TrameDef
% Programmeurs:             JG,
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
[x,fe] = audioread('Tropical_JG_2019-02-23_09-33-49.wav');

fmax = fe/2;
fgrad = fmax./(length(x)./2);

% FFT du signal de référence
X = fft(x,length(x)./2);
Xm = abs(X);
Xp = angle(X);
f = 0:fgrad:fmax-fgrad;

figure(1)
subplot(2,1,1)
plot(f,Xm)
subplot(2,1,2)
plot(f,Xp)