%% getEZWEED
% Programmeurs:             JG,
% Date de cr�ation:         2019-03-23
% Derni�re modification:    2019-03-23
% Description:              
% Ce script sert � tester la fonctionnalit� de EZWEED.m
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

% D�finition de constantes
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
    %% Enregistrement du signal d'entr�e 
    % Cette partie ce ferait par interrruption dans CCS
    Enregistrement(e) = x_16(i);
    e = e + 1;

    if (e > LONGUEUR_TRAME)
        if (ComputingTrame == 0)
            x_fn = Enregistrement;
            % La trame enregistr�e est pr�te � �tre envoy�
            ComputingTrame = 1;
        end
        e = 1;
    end
    %% Machine � �tat  
    % State machine principale
    if (State == IDLE)
        %% IDLE
        % D�tection de seuil
        enveloppe = filter(b,[1],abs(Enregistrement));
        if (max(enveloppe) > SEUIL) % valeur arbitraire (normalis�e)
           State = COMPUTING;
        end
    elseif (State == COMPUTING)
        %% Computing
        % Detection de fin
        enveloppe = filter(b,[1],abs(Enregistrement));
        if (max(enveloppe) < SEUIL) % valeur arbitraire (normalis�e)
           State = RESULT;
        end
        
        % Trame pr�te � �tre utilis�e
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

            % D�tection de la F0
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
        % On indique si le mot � �t� d�tect�
        if (CompteF0./CompteTotal > Acceptabilite)
            display('Vous avez dit EZWEED');
        else
            display('?');
        end
    end
end
end