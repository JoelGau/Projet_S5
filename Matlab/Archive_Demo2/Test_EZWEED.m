%% Test_EZWEED
% Programmeurs:             JG,
% Date de création:         2019-03-23
% Dernière modification:    2019-03-23
% Description:              
% Ce script sert à tester la fonctionnalité de getEZWEED.m
%% Core
clc
clear all
close all

myVoice = audiorecorder(16000,16,1);
% Define callbacks to show when
% recording starts and completes.
myVoice.StartFcn = 'disp(''Start speaking.'')';
myVoice.StopFcn = 'disp(''End of recording.'')';
recordblocking(myVoice, 5);

x_16 = getaudiodata(myVoice, 'double');

getEZWEED(x_16,16000)