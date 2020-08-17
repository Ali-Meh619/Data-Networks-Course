%stop and wait
%%
clear
Tt=1e-3:1e-3:2e-2;
Tp=1.5e-3;
p=0.1;
A=zeros(1,10000);
%w=10:10:500;
%%
%Tt
for i=1:size(Tt,2)
    
x=eff_SW(A,Tt(1,i),Tp,p);
ff(1,i)=x;
end
%%
plot(Tt,ff)
xlabel('Transmission Delay')
ylabel('Efficiency')
title('Stop and Wait')
%%
clear
Tt=1e-3;
Tp=1.5e-3:1e-3:2e-2;
p=0.1;
A=zeros(1,10000);
%w=10:10:500;
%%
%Tp
for i=1:size(Tp,2)
    
x=eff_SW(A,Tt,Tp(1,i),p);
ff(1,i)=x;
end
%%
plot(Tp,ff)
xlabel('Propagation Delay')
ylabel('Efficiency')
title('Stop and Wait')
%%
clear
Tt=1e-3;
Tp=1.5e-3;
p=0.1:0.02:0.5;
A=zeros(1,10000);
%w=10:10:500;
%%
%p
for i=1:size(p,2)
    
x=eff_SW(A,Tt,Tp,p(1,i));
ff(1,i)=x;
end
%%
plot(p,ff)
xlabel('Probability of Loss')
ylabel('Efficiency')
title('Stop and Wait')
%%
%GO_back N
%%
clear
Tt=1e-3:1e-3:2e-2;
Tp=1.5e-3;
p=0.1;
A=zeros(1,10000);
w=500;
%%
%Tt
for i=1:size(Tt,2)
    
x=eff_GBN(A,Tt(1,i),Tp,p,w);
ff(1,i)=x;
end
%%
plot(Tt,ff)
xlabel('Transmission Delay')
ylabel('Efficiency')
title('Go Back N')
%%
clear
Tt=1e-3;
Tp=1.5e-3:1e-3:2e-2;
p=0.1;
A=zeros(1,10000);
w=500;
%%
%Tp
for i=1:size(Tp,2)
    
x=eff_GBN(A,Tt,Tp(1,i),p,w);
ff(1,i)=x;
end
%%
plot(Tp,ff)
xlabel('Propagation Delay')
ylabel('Efficiency')
title('Go Back N')
%%
clear
Tt=1e-3;
Tp=1.5e-3;
p=0.1:0.02:0.5;
A=zeros(1,10000);
w=500;
%%
%p
for i=1:size(p,2)
    
x=eff_GBN(A,Tt,Tp,p(1,i),w);
ff(1,i)=x;
end
%%
plot(p,ff)
xlabel('Probability of Loss')
ylabel('Efficiency')
title('Go Back N')

%%
clear
Tt=1e-3;
Tp=1.5e-3;
p=0.1;
A=zeros(1,10000);
w=500:150:2000;
%%
%window
for i=1:size(w,2)
    
x=eff_GBN(A,Tt,Tp,p,w(1,i));
ff(1,i)=x;
end
%%
plot(w,ff)
xlabel('Size Of Window')
ylabel('Efficiency')
title('Go Back N')
%%
%Selective_Repeat
%%
clear
Tt=1e-3:1e-3:2e-2;
Tp=1.5e-3;
p=0.1;
A=zeros(1,10000);
w=500;
%%
%Tt
for i=1:size(Tt,2)
    
x=eff_SR(A,Tt(1,i),Tp,p,w);
ff(1,i)=x;
end
%%
plot(Tt,ff)
xlabel('Transmission Delay')
ylabel('Efficiency')
title('Selective Repeat')
%%
clear
Tt=1e-3;
Tp=1.5e-3:1e-3:2e-2;
p=0.1;
A=zeros(1,10000);
w=500;
%%
%Tp
for i=1:size(Tp,2)
    
x=eff_SR(A,Tt,Tp(1,i),p,w);
ff(1,i)=x;
end
%%
plot(Tp,ff)
xlabel('Propagation Delay')
ylabel('Efficiency')
title('Selective Repeat')
%%
clear
Tt=1e-3;
Tp=1.5e-3;
p=0.1:0.02:0.6;
A=zeros(1,10000);
w=500;
%%
%Tt
for i=1:size(p,2)
    
x=eff_SR(A,Tt,Tp,p(1,i),w);
ff(1,i)=x;
end
%%
plot(p,ff)
xlabel('Probability of Loss')
ylabel('Efficiency')
title('Selective Repeat')
%%
function e=prob(p)



a=rand(1);

if a>p
    e=1;
else
    e=0;
end



end

function ef=eff_SW(A,Tt,Tp,p)
Tout=8e-3;
q=zeros(2,size(A,2));
qq=1;
i=1;
while qq==1
    
   a=prob(p);
   
   if a==1
   
       b=prob(p);
       
       if b==1
                
      w=ceil((Tt+2*Tp)/Tout);
      if w>=1
      q(1,i)=q(1,i)+w;
      q(2,i)=1;
      i=i+1;
      
      else
      q(1,i)=q(1,i)+1;
      q(2,i)=1;
      i=i+1;    
      end
      
       else
           
      q(1,i)=q(1,i)+1;
       end
   else
   q(1,i)=q(1,i)+1;
   
   end


   
      if q(2,size(A,2))==1
          break;
      end
       
end


xx=sum(q,2);
ef=size(A,2)/xx(1,1);

end

function ef=eff_GBN(A,Tt,Tp,p,w)

Tout=12e-3;
q=zeros(2,size(A,2));
qq=1;
i=1;

while qq==1
    
   a=prob(p);
   y=min(w,sum(q(2,:)==0));
   
   if a==1
   b=prob(p);
   
   if b==1
      f=ceil((Tt+2*Tp)/Tout);
      if f>=1
      q(1,i)=q(1,i)+y*f;
      q(2,i)=1;
      i=i+1;
      else
      q(1,i)=q(1,i)+1;
      q(2,i)=1;
      i=i+1;  
      end
      
   else
     q(1,i)=q(1,i)+y;  
   end
   
   else
       
      q(1,i)=q(1,i)+y;
       
   end
    
    
   if q(2,size(A,2))==1
          break;
      end
   
    
    
end

xx=sum(q,2);
ef=size(A,2)/xx(1,1);

end


function ef=eff_SR(A,Tt,Tp,p,w)

Tout=12e-3;
q=zeros(2,size(A,2));
qq=1;
i=1;
while qq==1
    
   a=prob(p);
   
   if a==1
   
       b=prob(p);
       
       if b==1
                
      w=ceil((Tt+2*Tp)/Tout);
      if w>=1
      q(1,i)=q(1,i)+w;
      q(2,i)=1;
      i=i+1;
      
      else
      q(1,i)=q(1,i)+1;
      q(2,i)=1;
      i=i+1;    
      end
      
       else
           
      q(1,i)=q(1,i)+1;
       end
   else
   q(1,i)=q(1,i)+1;
   
   end


   
      if q(2,size(A,2))==1
          break;
      end
       
end


xx=sum(q,2);
ef=size(A,2)/xx(1,1);

end


