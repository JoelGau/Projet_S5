%% CorrelationCroisee
% Programmeurs:             JG, MSP
% Date de cr�ation:         2019-02-23
% Derni�re modification:    2019-02-23
% Description:              
% Cette fonction prend en input 2 signaux de m�me longueur. Elle renvoit en
% output la corr�lation crois�e des 2 signaux. Ce code devrait �tre assez
% de base pour que sont impl�mentation en langage c soit facile.
%% Core
function [C] = CorrelationCroisee(x1,x2)
    % Mesure de la longueur des signaux d'entr�es
    Lx1 = length(x1);
    Lx2 = length(x2);
    
    % On pad de z�ros le signal le plus court
    if Lx1 > Lx2
        x2 = [x2 zeros(1,Lx1-Lx2)];
    elseif Lx1 < Lx2
        x1 = [x1,zeros(1,Lx2-Lx1)]; 
    end
    
    Lx1 = length(x1);
    Lx2 = length(x2);
    
    % D�terminer la longueur du signal de sortie
    Lc = Lx1 + Lx2 - 1;
    C = zeros(1,Lc);
    
    Kmin1 = 1;
    Kmax1 = 1;
    
    Kmin2 = round(Lc./2);
    Kmax2 = Kmin2;
    
    for i = 1:Lc
        newx1 = x1(Kmin1:Kmax1);
        newx2 = x2(Kmin2:Kmax2);
        n = length(newx1);
        C(i) = sum(newx1.*newx2);
        if (i < round(Lc./2))
            Kmax1 = Kmax1 + 1;
            Kmin2 = Kmin2 - 1;
        elseif (i >= round(Lc./2))
            Kmin1 = Kmin1 + 1;
            Kmax2 = Kmax2 - 1;
        end
    end
end