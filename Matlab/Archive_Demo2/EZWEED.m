%% RD_EZWEED
% Programmeurs:             JG,
% Date de cr�ation:         2019-03-21
% Derni�re modification:    2019-03-21
% Description:              
% Ce programme traite des signaux "EZWEED". Le but de ce script est de
% d�terminer un logique pour d�tecter le mot "EZWEED".
%% Core
clc
clear all
close all

% Constante
IDLE = 0;
COMPUTING = 1;
RESULT = 2;

SEUIL = 0.1;

% Filtre FIR pour enveloppe
b = fir1(400,pi./1000);

% Filtre Passe bande pour la F0


% EZWEED
[x_48,fe_48] = audioread('.\Signaux\EZWEED_JG_2019-03-19_19-50-39.wav');

% Diminution de la fr�quence d'�chantillonage � 16 kHz
x_16 = downsample(x_48(:,1),4);
fe_16 = fe_48/4;

% D�finition de constantes
LONGUEUR_TRAME = 1024;
INTERVALLE_TRAME = LONGUEUR_TRAME./2;

% Initialisation de variable globales
State = IDLE;
GO = 0;
TimeGo = 0;
STOP = 0;
TimeStop = 0;

% Cette boucle for permet de simuler l'arriver du signal en continue
for i = [1:1:Longueur_Signal]
    
    % D�terminer l'indice de fin de trame
    ibas = i - LONGUEUR_TRAME;
    if ((i - LONGUEUR_TRAME) < 1)
       ibas = 1; 
    end
    
    % Signal qui rentre dans l'enveloppe pour le filtre
    x_fn = x_16(ibas:i);
    
    % Calcul de l'enveloppe
    enveloppe = filter(b,[1],abs(x_fn));
    
    % State machine principale
    if (State == IDLE)
        % Detection de seuil
        if (max(enveloppe) > SEUIL) % valeur arbitraire (normalis�e)
           State = COMPUTING;
        end
    elseif (State == COMPUTING)
        % Detection de fin
        if (max(enveloppe) < SEUIL) % valeur arbitraire (normalis�e)
           State = RESULT;
        end
        % Filtre passe-bande
        x_filtered = filter(b_bande,a_bande,x_fn);
        % Fenetrage du signal d'entr�e (x) -> x_hm
        x_fn = x_16(i:i + LONGUEUR_TRAME-1);
        x_hm = F_hm.*x_fn;
        
    elseif (State == RESULT)
        % On indique si le mot � �t� d�tect�
        Resutltat = 1;
        
    end
end