%% RD_RP
% Programmeurs:             JG,
% Date de création:         2019-03-15
% Dernière modification:    2019-03-16
% Description:              
% Ce sript est une exploration pour déterminer une méthode/algorithme dans
% le but de faire de la reconnaissance de la parole. Nos mots de test se
% retrouvent dans le répertoire Signaux. Le mot test utilisé est
% "tropicale".
%% Core
clc
clear all
close all

% Enregistrements
[x_48,fe_48] = audioread('.\Signaux\Tropical_EAD_2019-02-26_10-08-43.wav');
x_16 = downsample(x_48(:,1),4);
fe_16 = fe_48/4;
% [x2,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_JG_2019-02-23_09-33-49.wav');
% [x3,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_JG_2019-02-26_10-06-01.wav');
% [x4,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_JL_2019-02-26_10-10-32.wav');
% [x5,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_MSP_2019-02-26_10-08-08.wav');
% [x6,fe] = audioread('C:\Users\jgaud\Git_Projet_S5\Matlab\Archive_Demo1\Signaux\Tropical_SV_2019-02-26_10-13-00.wav');

% Définition de constantes
LONGUEUR_TRAME = 1024;
INTERVALLE_TRAME = LONGUEUR_TRAME./2;

% Éventuellement, dans le dsk, le fenetrage se ferait en temps réel.
Longueur_Signal = length(x_16);

% Filtre FIR pour enveloppe
b = fir1(400,pi./1000);
% enveloppe2 = filter(b,[1],abs(x_16));
% figure(1)
% hold on
% plot(x_16,'r')
% plot(enveloppe2,'b')
% hold off
% 

% X_FFT = complex(zeros(1,1024),zeros(1,round(Longueur_Signal./512)));
X_FFT = ones(LONGUEUR_TRAME./2,round(Longueur_Signal./512)).*complex(0,0);
k = 1;
Computing = 0;
F_hm = hamming(LONGUEUR_TRAME);
for i = [1:INTERVALLE_TRAME:Longueur_Signal-LONGUEUR_TRAME]
    
    % Fenetrage du signal d'entrée (x) -> x_hm
    x_fn = x_16(i:i + LONGUEUR_TRAME-1);
    x_hm = F_hm.*x_fn;
    
    % Detection de seuil
    if not(Computing)
        enveloppe = filter(b,[1],abs(x_fn));
        if (max(enveloppe) > 0.3) % valeur arbitraire (normalisée)
           Computing = 1; 
        end
    else
        % FFT
        tampon = fft(x_hm);
        X_FFT(:,k) = tampon(1:LONGUEUR_TRAME./2);
        k = k + 1;
    end
end

figure(1)
surf(abs(X_FFT))


