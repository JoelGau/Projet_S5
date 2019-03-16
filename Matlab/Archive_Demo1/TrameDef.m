%% TrameDef
% Programmeurs:             JG,LPBR
% Date de cr�ation:         2019-02-25
% Derni�re modification:    2019-02-25
% Description:              
% Le script suivant sert � d�terminer la longueur d'une trame lors d'un
% enregistrement. Pour ce faire, on prend notre �chantillon de son, on fait
% sa FFT et on isole la fr�quence utile la plus basse � l'int�rieur. Par la
% suite, on est en mesure de retrouver la p�riode la plus longue de notre
% signal. La trame sera d'une longueur de cette p�ridode x2.
%% Core 48 kHz
clc
clear all
close all

%On load le signal de r�f�rence
[y,Fs] = audioread('SonGraveO.wav');
T = 1/Fs;
L = length(y);
t = (0:L-1)*T;
w = hamming(L);
Y = y.*w; %Fen�trage

FFT = fft(Y);
P2 = abs(FFT/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
P = 20*log10(P1/max(abs(P1)));
f = Fs*(0:(L/2))/L;

% Affichage FFT du signal d'origine
figure(1)
semilogx(f(2:end-1),P(2:end-1))
grid
xlabel('Frequency (Hz)')
ylabel('Amplitude (dB)')
title('Son "O"')

% Selon le graph, la freq min est � 100 Hz environ 
% tmin_trame = 2/freq = 20 ms approximativement

%% Core 16 kHz
clc
clear all
%close all

%On load le signal de r�f�rence
[y,Fs] = audioread('SonGraveO_16kHz.wav');
T = 1/Fs;
L = length(y);
t = (0:L-1)*T;
w = hamming(L);
Y = y.*w; %Fen�trage

FFT = fft(Y);
P2 = abs(FFT/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
P = 20*log10(P1/max(abs(P1)));
f = Fs*(0:(L/2))/L;

% Affichage FFT du signal d'origine
figure(2)
semilogx(f(2:end-1),P(2:end-1))
grid
xlabel('Frequency (Hz)')
ylabel('Amplitude (dB)')
title('Son "O"')

% Selon le graph, la freq min est � 100 Hz environ 
% tmin_trame = 2/freq = 20 ms approximativement