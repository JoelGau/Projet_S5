%% teach_EZWEED
% Programmeurs:             JG,
% Date de création:         2019-03-28
% Dernière modification:    2019-03-30
% Description:              
% Cette fonction permet de déterminer la F0 d'un signal en utilisant la
% méthode par autocorrélation vue à l'APP 6. Par la suite, cette fonction
% appele getF0 qui elle prend l'autocorrélation en entrée et redonne la
% fréquence F0 en sortie.

function [F0] = teachEZWEED(x_16,fe_16)
% Définition de constantes
LONGUEUR_TRAME = 1024;
LONGUEUR_TRAME_HALF = LONGUEUR_TRAME./2;
F_hm = hamming(LONGUEUR_TRAME);

% Déclaration de variables globales
Enregistrement = zeros(1,LONGUEUR_TRAME);

% Filtre Passe bande pour la F0

Longueur_Signal = length(x_16);
% Cette boucle for permet de simuler l'arriver du signal en continue
for i = [1:1:Longueur_Signal]
    %% Enregistrement du signal d'entrée 
    % Cette partie ce ferait par interruption dans CCS
    Enregistrement(e) = x_16(i);
    e = e + 1;

    if (e > LONGUEUR_TRAME)
        if (ComputingTrame == 0)
            x_fn = Enregistrement;
            % La trame enregistrée est prête à être envoyé
            ComputingTrame = 1;
        end
        e = 1;
    end
    
    if (State == COMPUTING)
        % Application d'une fenêtre de hamming
        x_hm = F_hm.*x_fn;

        % Faire une autoCorrelation du signal
        Corr = CorrelationCroisee(x_hm,x_hm);
        
        % Isoler la F0 du signal avec la fonction getF0
        F0 = getF0(Corr, LONGUEUR_TRAME, fe_16);
        
        % Faire la somme de toutes les F0 dans le but d'en trouver la
        % moyenne.
        F0moy = F0moy + F0;
        
        
    end
    
end