%% TrameDef
% Programmeurs:             JG,
% Date de cr�ation:         2019-02-25
% Derni�re modification:    2019-02-25
% Description:              
% Le script suivant sert � d�terminer la longueur d'une trame lors d'un
% enregistrement. Pour ce faire, on prend notre �chantillon de son, on fait
% sa FFT et on isole la fr�quence utile la plus basse � l'int�rieur. Par la
% suite, on est en mesure de retrouver la p�riode la plus longue de notre
% signal. La trame sera d'une longueur de cette p�ridode x2.
%% Core
clc
clear all
close all

%On load le signal de r�f�rence
[x,fe] = audioread('Tropical_JG_2019-02-23_09-33-49.wav');

fmax = fe/2;
fgrad = fmax./(length(x)./2);

% FFT du signal de r�f�rence
X = fft(x,length(x)./2);
Xm = abs(X);
Xp = angle(X);
f = 0:fgrad:fmax-fgrad;

figure(1)
subplot(2,1,1)
plot(f,Xm)
subplot(2,1,2)
plot(f,Xp)