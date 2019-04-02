%% getF0
% Programmeurs:             JG,
% Date de création:         2019-03-18
% Dernière modification:    2019-03-30
% Description:              
% Cette fonction trouve la distance entre 2 peaks (ce qui correspond à la
% fréquence fondamentale du signal autocorrélée), et retourne la fréquence
% fondamentale conséquente.
%% Core
function [F0] = getF0(autocorr, LONGUEUR_TRAME, FS)
    % Comme l'autocorrélation est symétrique, on traite seulement la m
    % moitié du signal.
    
    % Constantes d'états
    FIRST_MAX = 0;
    FIRST_ZERO = 1;
    SECOND_ZERO = 2;
    SECOND_MAX = 3;
    
    amp_max = 0;
    state = FIRST_MAX;
    for i = 1:1:LONGUEUR_TRAME
        if (state == FIRST_MAX)
            % Trouver le premier maximum
            if (autocorr(i) > amp_max)
               amp_max = autocorr(i); 
            else
               FirstPeak = i - 1; 
               state = FIRST_ZERO;
            end
        elseif (state == FIRST_ZERO)
            % Passer en dessous de zero
            if (autocorr(i) < 0)
               state = SECOND_ZERO; 
            end
        elseif (state == SECOND_ZERO)
            % Passer au dessus de zero
            if (autocorr(i) > 0)
               state = SECOND_MAX; 
            end
        elseif (state == SECOND_MAX)
            % Trouver le deuxième maximum
            if (autocorr(i) > amp_max)
               amp_max = autocorr(i); 
            else
               SecondPeak = i - 1; 
               break;
            end
        end
    end
    % Calcul de la F0
    T = (SecondPeak - FirstPeak)./FS;
    F0 = 1./T;
end