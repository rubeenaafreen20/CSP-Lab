function decoded = ml_detection( receivedSignal,n)
%ML Decoding; n=1 for BPSK and n=2 for QPSK
if n==1
    ak=[-1,1];
        for i=1:2
        dist(i)=(receivedSignal-ak(i))^2;
        end
        [Y,index]=min(dist);
        decoded=ak(index);

elseif n==2
    ak1=[complex(1,1),complex(1,-1),complex(-1,1),complex(-1,-1)]; 
    for j=1:4
        dist1(j)=abs(receivedSignal-ak1(j))^2;
    end
        [Y,index1]=min(dist1);
        decoded=ak1(index1);
end    
end

