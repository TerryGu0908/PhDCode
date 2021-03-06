%% Test bandDetect.m
% 
% Most recent change - 9/9/2011
%
% Copyright 2011, Mark Davenport, Michael Wakin
%
% This file is part of DPSS Approximation and Recovery Toolbox version 1.0.
%
%    DART is free software: you can redistribute it and/or modify
%    it under the terms of the GNU General Public License as published by
%    the Free Software Foundation, either version 3 of the License, or
%    (at your option) any later version.
%
%    DART is distributed in the hope that it will be useful,
%    but WITHOUT ANY WARRANTY; without even the implied warranty of
%    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%    GNU General Public License for more details.
%
%    You should have received a copy of the GNU General Public License
%    along with DART.  If not, see <http://www.gnu.org/licenses/>.

%% Initialize
clear all; close all;

addpath('../')

%% Set signal/algorithm parameters
N = 1024*4;
B = 1/256;
K = 5; 
opts.N = N; opts.B = B; opts.K = K;
opts.type = 'randtones'; 
opts.TPB = 50;  

%  DPSS KNOBS
dpssSize = N*B+40;  
dpssWidth = N*B/2;     

%% Compute projection
[x supp] = generateSignal(opts); % Generate signal
modulator = generateModulator(N,B); % Generate modulator matrix
PsiRecover = dpss(N,dpssWidth,dpssSize); % Construct base DPSS basis
PsiDetect = PsiRecover; % Use same basis for detection as recovery
detectOpts.alg = 'blockOMP'; % Select detection algorithm

% Project x onto the set of K-block-sparse signals
[supp_hat x_hat] = bandDetect(x,K,PsiDetect,PsiRecover,modulator,detectOpts);

%% Display results
disp(['Recovery SNR: ' num2str(20*log10(norm(x)/norm(x-x_hat))) 'dB']);
disp(['Original support : ' mat2str(sort(supp))]);
disp(['Recovered support : ' mat2str(sort(supp_hat))]);

figure(1)
plot([1:N]/N-.5,abs(fftshift(fft(x))))
hold on
plot([1:N]/N-.5,abs(fftshift(fft(x_hat))),'r')
title('Frequency domain')
legend('Original','Recovered')