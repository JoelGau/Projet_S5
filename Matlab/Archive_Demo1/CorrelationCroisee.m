%% CorrelationCroisee
% Programmeurs:             JG,
% Date de création:         2019-02-23
% Dernière modification:    2019-02-23
% Description:              
% Cette fonction prend en input 2 signaux de même longueur. Elle renvoit en
% output la corrélation croisée des 2 signaux. Ce code devrait être assez
% de base pour que sont implémentation en langage c soit facile.
%% Core
function [y] = CorrelationCroisee(x1,x2)
    % Mesure de la longueur des signaux d'entrées
    Lx1 = length(x1);
    Lx2 = length(x2);
    
    if Lx1 > Lx2
        error('Le signal 1 est plus grand que le signal 2')
    end
    Lxx = abs(Lx1-Lx2)+1;
    % Déterminer la longueur du signal de sortie
    Ly = Lx1 + Lx2 - 1;
    y = zeros(1,Ly);
    
    % Implémentation de la corrétion
    kmin = 0;
    kmax = 0;
    for i = 1:1:Ly %index de sortie
        
        for k = kmin:1:kmax %index d'addition
            k
            y(i) = y(i) + x1(Lx1-k).*x2(k+1)
        end
        % Opération pour déplacer la fenetre de multiplication du signal x1
        % sur le signal 2 dans le but de faire la multilplication point par
        % point.
        if kmax < Lx1-1
            kmax = kmax + 1;
        elseif kmax >= Lx1-1 && kmax <= Lx2-1
            kmax = kmax + 1;
            kmin = kmin + 1;
        elseif kmax >= Lxx && kmin < kmax
            kmin = kmin + 1;
        end
    end
end