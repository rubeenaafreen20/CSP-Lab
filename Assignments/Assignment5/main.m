%%                          Generate Random Binary Data
clc;
clear all;
n_bpsk=1;
num_bit = 10e4;
receivedSignal_bpsk=zeros(1,num_bit);
SNRdB=0:10; % SNR in dB
SNR_lin=10.^(SNRdB/10);
ak_bpsk=[-1,1];
Es_bpsk=(1/2)*sum(ak_bpsk.^2);
n_qpsk=2;
ak_qpsk=(1/sqrt(2))*[complex(1,1),complex(1,-1),complex(-1,1),complex(-1,-1)];            %QPSK Symbols (normalized)
Es_qpsk=(1/4)*sum(abs(ak_qpsk).^2);                                                     %Symbol energy=1
for k=1:length(SNRdB)
    sd_bpsk= sqrt(Es_bpsk/(2*SNR_lin(k)));                  %sigma for BPSK
    sym_error_bpsk=0;
    bit_error_bpsk=0;
    
    sd_qpsk= sqrt(Es_qpsk/(2*SNR_lin(k)));                  %sigma for QPSK
    sym_error_qpsk=0;
    bit_error_qpsk=0;
    for i = 1:num_bit    
        %%          BPSK & QPSK generation and decoding
        bits_bpsk = randi([0 1]);
        bits_qpsk =randi([0 1],1,2);
        signalSpace=digital_modulation(bits_bpsk,n_bpsk);           %Mapping to symbols BPSK
        signal_qpsk=digital_modulation(bits_qpsk,n_qpsk);           %Mapping to symbols QPSK
        awgn_bpsk=sd_bpsk* randn;
        awgn_qpsk=sd_qpsk*(randn+1i*randn);
        receivedSignal_bpsk=signalSpace'+awgn_bpsk;
        rxed_sig_qpsk=signal_qpsk+awgn_qpsk;
        decoded_symbol_bpsk=ml_detection(receivedSignal_bpsk,n_bpsk);
        decoded_qpsk=ml_detection(rxed_sig_qpsk,n_qpsk);
        estimate_bits=(decoded_symbol_bpsk+1)/2;
        if decoded_qpsk==complex(1,1)
            estimate_bits_qpsk=de2bi(0,2);
        elseif decoded_qpsk==complex(1,-1)
            estimate_bits_qpsk=de2bi(1,2);
        elseif decoded_qpsk==complex(-1,1)
            estimate_bits_qpsk=de2bi(2,2);
        elseif decoded_qpsk==complex(-1,-1)
            estimate_bits_qpsk=de2bi(3,2);
        end
        %%  error of BPSK
            if signalSpace~=decoded_symbol_bpsk
                sym_error_bpsk=sym_error_bpsk+1;
            if estimate_bits~=bits_bpsk
                bit_error_bpsk=bit_error_bpsk+1;
            end
            end

        %%  error of QPSK
         if (bi2de(abs(estimate_bits_qpsk-bits_qpsk))~=0)
            sym_error_qpsk=sym_error_qpsk+1;
         end
            %for m=1:2
            %if (estimate_bits_qpsk(:,m)==0 && bits_qpsk(:,m)==1)||(estimate_bits_qpsk(:,m)==0 && bits_qpsk(:,m)==1)
            %if (estimate_bits_qpsk(:,m)~=bits_qpsk(:,m))
            bit_error_qpsk=bit_error_qpsk+nnz(estimate_bits_qpsk-bits_qpsk);
            %end
            %end
    end
        sym_error_bpsk=sym_error_bpsk/num_bit;            %num_bit=num_symbols in bpsk
        bit_error_bpsk=bit_error_bpsk/num_bit;
        sym_error_qpsk=sym_error_qpsk/num_bit;            %num_bit=num_symbols in qpsk
        bit_error_qpsk=bit_error_qpsk/(2*num_bit);         

    BER_bpsk(k)=bit_error_bpsk;
    SER_bpsk(k)=sym_error_bpsk;
    BER_qpsk(k)=bit_error_qpsk;
    SER_qpsk(k)=sym_error_qpsk;
end
display(BER_bpsk);
display(SER_bpsk);
display(BER_qpsk);
display(SER_qpsk);
BER_th_bpsk=(1/2)*erfc(sqrt(SNR_lin));
SER_th_bpsk=BER_th_bpsk;
BER_th_qpsk=BER_th_bpsk;
BER_th_qpsk=erfc(sqrt(SNR_lin));
 
 
    %%              plot of BER for bpsk
    
    subplot(2,2,1);
    axis([0 10 10^-5 1]);
    semilogy(SNRdB,BER_bpsk,'o','linewidth',2.5),grid on,grid minor,hold on;
    semilogy(SNRdB,BER_th_bpsk,'r','linewidth',2.5);
    title('BER vs  SNR for BPSK');
    xlabel(' SNR(dB)');
    ylabel('BER');
    legend('simulation','theoretical');
    %%          plot of SER for bpsk
    SER_th_bpsk=BER_th_bpsk;
    subplot(2,2,2); 
    axis([0 10 10^-5 1]);
    semilogy(SNRdB,SER_bpsk,'o','linewidth',2.5),grid on,grid minor,hold on;
    semilogy(SNRdB,SER_th_bpsk,'r','linewidth',2.5);
    title(' SER vs SNR for BPSK');
    xlabel(' SNR(dB)');
    ylabel('BER');
    legend('simulation','theoretical');
        %%          plot of BER for Qpsk
    BER_th_qpsk=BER_th_bpsk;
    subplot(2,2,3); 
    axis([0 10 10^-5 1]);
    semilogy(SNRdB,BER_qpsk,'o','linewidth',2.5),
    grid on,grid minor,
    hold on;
    semilogy(SNRdB,BER_th_qpsk,'r','linewidth',2.5);
    title(' BER vs SNR for QPSK');
    xlabel(' SNR(dB)');
    ylabel('BER');
    legend('simulation','theoretical');
       %%          plot of SER for Qpsk
    SER_th_qpsk=2*BER_th_bpsk;
    subplot(2,2,4);
    axis([0 10 10^-5 1]);
    semilogy(SNRdB,SER_qpsk,'o','linewidth',2.5),
    grid on,grid minor,
    hold on;
    semilogy(SNRdB,SER_th_qpsk,'r','linewidth',2.5);
    title(' SER vs SNR for QPSK modulation');
    xlabel(' SNR(dB)');
    ylabel('BER');
    legend('simulation','theoretical');
    
   