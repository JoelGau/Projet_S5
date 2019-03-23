%% getEZWEED
% Programmeurs:             JG,
% Date de création:         2019-03-23
% Dernière modification:    2019-03-23
% Description:              
% Ce script sert à tester la fonctionnalité de EZWEED.m
%% Core

function getEZWEED(x_16,fe_16)
% Constante
IDLE = 0;
COMPUTING = 1;
RESULT = 2;

SEUIL = 0.1;

% Filtre FIR pour enveloppe
b = fir1(50,pi./1000);

% Filtre Passe bande pour la F0

Longueur_Signal = length(x_16);

% Définition de constantes
LONGUEUR_TRAME = 1024;
LONGUEUR_TRAME_HALF = LONGUEUR_TRAME./2;
F0min = 10;
F0max = 15;
Acceptabilite = 0.5;
F_hm = hamming(LONGUEUR_TRAME);

IDLE = 0;
COMPUTING = 1;
RESULT = 2;

% Initialisation de variable globales
State = IDLE;
CompteF0 = 0;
CompteTotal = 0;
Enregistrement = zeros(1,LONGUEUR_TRAME);
e = 1;
ComputingTrame = 0;

% Cette boucle for permet de simuler l'arriver du signal en continue
for i = [1:1:Longueur_Signal]
    %% Enregistrement du signal d'entrée 
    % Cette partie ce ferait par interrruption dans CCS
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
    %% Machine à État  
    % State machine principale
    if (State == IDLE)
        %% IDLE
        % Détection de seuil
        enveloppe = filter(b,[1],abs(Enregistrement));
        if (max(enveloppe) > SEUIL) % valeur arbitraire (normalisée)
           State = COMPUTING;
        end
    elseif (State == COMPUTING)
        %% Computing
        % Detection de fin
        enveloppe = filter(b,[1],abs(Enregistrement));
        if (max(enveloppe) < SEUIL) % valeur arbitraire (normalisée)
           State = RESULT;
        end
        
        % Trame prête à être utilisée
        if (ComputingTrame == 1)
            % Fenetrage
            x_hm = F_hm'.*x_fn;

            % FFT
            X = abs(fft(x_hm));

            % Lissage de la FFT
            newX(1) = mean([X(1) X(2)]);
            newX(LONGUEUR_TRAME_HALF) = mean([X(LONGUEUR_TRAME_HALF-1) X(LONGUEUR_TRAME_HALF)]);
            for k = [2:1:LONGUEUR_TRAME_HALF-1]
               newX(k) = mean([X(k-1) X(k) X(k+1)]); 
            end

            % Détection de la F0
            [pks,loc] = findpeaks(newX,'NPeaks',1);
            if not(isempty(loc))
                if ((loc >= F0min) && (loc <= F0max))
                    CompteF0 = CompteF0 + 1;
                end
            end
            CompteTotal = CompteTotal + 1;
            ComputingTrame = 0; 
        end
    elseif (State == RESULT)
        %% RESULT
        % On indique si le mot à été détecté
        if (CompteF0./CompteTotal > Acceptabilite)
            display('Vous avez dit EZWEED');
        else
            display('?');
        end
    end
end
end