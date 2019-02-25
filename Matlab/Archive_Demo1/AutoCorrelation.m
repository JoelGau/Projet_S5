%% AutoCorrelation
% Programmeurs:             JG, MSP
% Date de création:         2019-02-23
% Dernière modification:    2019-02-23
% Description:              
% Ce script sert de plan de test automatique pour la fonction de
% CorrelationCroisee.m développé. Les différents tests sont décrit dans les
% sections plus basses.
%% Core
clc
clear all
close all

x1 = [1 2 3 4 5 5 4 3 2 1];
x2 = [1 1 1 1 1 1];


%[x,fe] = audioread('Tropical_JG_2019-02-23_09-33-49.wav');

y = xcorr(x1,x2);
y2 = CorrelationCroisee(x1,x2);

diff = y - y2;
%% Test 1: Longueur signal de sortie
clc
clear all
close all

x1 = [1 0 1 0];
x2 = [0 1 0 0];

y2 = CorrelationCroisee(x1,x2);
%% Test 2: 2 signaux orthogonaux
clc
clear all
close all

n = 1:100;

x1 = cos(pi.*n);
x2 = sin(pi.*n);

y = CorrelationCroisee(x1,x2);
%% Test 3: Comparaison de xcorr et CorrelationCroisee
clc
clear all
close all

n = 1:10;

x1 = cos(pi./4.*n);
x2 = sin(pi./4.*n);

y = CorrelationCroisee(x1,x2);
y2 = xcorr(x1,x2);
diff = y - y2;
%% Test 4: Comparaison de xcorr et CorrelationCroisee (longueur diff)
clc
clear all
close all

n1 = 1:10;
n2 = 1:20;

x1 = cos(pi./4.*n1);
x2 = sin(pi./4.*n2);

y = CorrelationCroisee(x1,x2);
y2 = xcorr(x1,x2);
diff = y - y2;
%% Test 5: Test d'inversion des signaux (longueur diff)
clc
clear all
close all

x1 = [1 0 1 0];
x2 = [1 1 0];

y = CorrelationCroisee(x1,x2);
y2 = CorrelationCroisee(x2,x1);
%% Test 6: Test d'inversion des signaux (longueur identique)
clc
clear all
close all

x1 = [1 0 1 0];
x2 = [0 1 1 0];

y = CorrelationCroisee(x1,x2);
y2 = CorrelationCroisee(x2,x1);