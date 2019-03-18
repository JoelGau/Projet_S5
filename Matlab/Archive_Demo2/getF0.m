%% getF0
% Programmeurs:             JG,
% Date de création:         2019-03-18
% Dernière modification:    2019-03-18
% Description:              
% Cette fonction est fortement inspirée de l'algorithme des professeurs
% (findErrAccordage.c) pour la problématique de l'APP6.
%% Core
function [F0] = getF0(xx, fmax, FS, L_TAMPON) 
	% Variables pour limiter la recherche dans l'autocorrélation
	delaiMin = FS/fmax;

	% Recherche du délai de la fréquence fondamentale
	amp_MAX = 0;
	for delai = 1:1:L_TAMPON
		if (xx(delai) > amp_MAX) % Si l'amplitude courrante de l'autocorrélation est 
								 % plus grande que les amplitudes précédentes
			amp_MAX =  xx(delai);	
			delaiF0 = delai;  		% Enregistrement du délai actuel
        end
    end
	if (delaiF0 >= delaiMin)
		F0 = FS/delaiF0; 	% Calcul de la fréquence fondamentale
	else
		F0 = 0;						% Aucune note ne semble être jouée
    end
end