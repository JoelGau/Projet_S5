%% Signal_Ref
% Programmeurs:             JG, MSP
% Date de création:         2019-02-26
% Dernière modification:    2019-02-26
% Description:              
% Ce script sert à lire les différents signaux en échantillons. On divise
% chacun des signaux en trame. Ensuite, on fait la FFT de chaque trame et
% on fait la moyenne avec les autres échantillons (autres signaux). À la 
% fin, on devrait se retrouver avec la FFT totale moyenne donc notre FFT de
% référence.
%% Core
% Constantes
clc
clear all
close all

% Lire les différents fichier audio
[x1,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_EAD_2019-02-26_10-08-43.wav');
[x2,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_JG_2019-02-23_09-33-49.wav');
[x3,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_JG_2019-02-26_10-06-01.wav');
[x4,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_JL_2019-02-26_10-10-32.wav');
[x5,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_MSP_2019-02-26_10-08-08.wav');
[x6,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_SV_2019-02-26_10-13-00.wav');

x1 = x1(:,1)';
x2 = x2(:,1)';
x3 = x3(:,1)';
x4 = x4(:,1)';
x5 = x5(:,1)';
x6 = x6(:,1)';

LONGUEURTRAME = 20e-3.*fe; 

% On divise en trame, on calcule la FFT de chaque trame et on fait la
% moyenne
hamm = hamming(LONGUEURTRAME)';

for i = 1:LONGUEURTRAME:LONGUEURTRAME.*100
    % On pose une fenetre de hamming sur notre trame et on fait sa FFT
    f1 = hamm.*x1(i:i+LONGUEURTRAME-1);
    F1 = fft(f1);
    F1r = real(F1);
    F1i = imag(F1);
    
    f2 = hamm.*x2(i:i+LONGUEURTRAME-1);
    F2 = fft(f2);
    F2r = real(F2);
    F2i = imag(F2);
    
    f3 = hamm.*x3(i:i+LONGUEURTRAME-1);
    F3 = fft(f3);
    F3r = real(F3);
    F3i = imag(F3);
    
    f4 = hamm.*x4(i:i+LONGUEURTRAME-1);
    F4 = fft(f4);
    F4r = real(F4);
    F4i = imag(F4);
    
    f5 = hamm.*x5(i:i+LONGUEURTRAME-1);
    F5 = fft(f5);
    F5r = real(F5);
    F5i = imag(F5);
    
    f6 = hamm.*x6(i:i+LONGUEURTRAME-1);
    F6 = fft(f6);
    F6r = real(F6);
    F6i = imag(F6);
    
    FFr = [F1r;F2r;F3r;F4r;F5r;F6r];  
    Fmoyr = mean(FFr,1);
    
    FFi = [F1i;F2i;F3i;F4i;F5i;F6i];  
    Fmoyi = mean(FFi,1);
    
end


