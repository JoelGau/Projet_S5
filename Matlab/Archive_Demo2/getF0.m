%% getF0
% Programmeurs:             JG,
% Date de cr�ation:         2019-03-18
% Derni�re modification:    2019-03-18
% Description:              
% Cette fonction est fortement inspir�e de l'algorithme des professeurs
% (findErrAccordage.c) pour la probl�matique de l'APP6.
%% Core
function [F0] = getF0(xx, fmax, FS, L_TAMPON) 
	% Variables pour limiter la recherche dans l'autocorr�lation
	delaiMin = FS/fmax;

	% Recherche du d�lai de la fr�quence fondamentale
	amp_MAX = 0;
	for delai = 1:1:L_TAMPON
		if (xx(delai) > amp_MAX) % Si l'amplitude courrante de l'autocorr�lation est 
								 % plus grande que les amplitudes pr�c�dentes
			amp_MAX =  xx(delai);	
			delaiF0 = delai;  		% Enregistrement du d�lai actuel
        end
    end
	if (delaiF0 >= delaiMin)
		F0 = FS/delaiF0; 	% Calcul de la fr�quence fondamentale
	else
		F0 = 0;						% Aucune note ne semble �tre jou�e
    end
end