function modulated = digital_modulation( bits,n)
if n==1                          %bpsk
    modulated=2*bits-1;               % 0 ---> -1 , 1---> 1
elseif n==2                     %For QPSK
    temp=bi2de(bits);
        if (temp ==0)
            modulated=complex(1,1);
        elseif (temp==1)
            modulated=complex(1,-1);
        elseif (temp==2)
            modulated=complex(-1,1);
        elseif (temp==3)
            modulated=complex(-1,-1);
        end
end

