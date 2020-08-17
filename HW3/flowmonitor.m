clc
clear
close all
%%loading xml
x_nonpersistant = [xml2struct('flow512kB_00.xml'),
xml2struct('flow512kB_01.xml'),
xml2struct('flow512kB_02.xml'),
xml2struct('flow512kB_03.xml'),
xml2struct('flow512kB_04.xml'),
xml2struct('flow512kB_05.xml'),
xml2struct('flow512kB_06.xml')];
    
    %%
x_aloha = [xml2struct('csma0.3_0.xml'),
        xml2struct('csma0.3_1.xml'),
        xml2struct('csma0.3_2.xml'),
        xml2struct('csma0.3_3.xml'),
        xml2struct('csma0.3_4.xml'),
        xml2struct('csma0.3_5.xml'),
        xml2struct('csma0.3_6.xml')];
    %%
x_p1 =[xml2struct('flow512kB_00.xml'),
        xml2struct('flow512kB_01.xml'),
        xml2struct('flow512kB_02.xml'),
        xml2struct('flow512kB_03.xml'),
        xml2struct('flow512kB_04.xml'),
        xml2struct('flow512kB_05.xml'),
        xml2struct('flow512kB_06.xml')];
    %%
x_p3 =[xml2struct('flow512kB_00.xml'),
        xml2struct('flow512kB_01.xml'),
        xml2struct('flow512kB_02.xml'),
        xml2struct('flow512kB_03.xml'),
        xml2struct('flow512kB_04.xml'),
        xml2struct('flow512kB_05.xml'),
        xml2struct('flow512kB_06.xml')];
    %%
    x_p5 = [xml2struct('flow512kB_00.xml'),
        xml2struct('flow512kB_01.xml'),
        xml2struct('flow512kB_02.xml'),
        xml2struct('flow512kB_03.xml'),
        xml2struct('flow512kB_04.xml'),
        xml2struct('flow512kB_05.xml'),
        xml2struct('flow512kB_06.xml')];

%% parsing xmls
BitRate = [25.5,37.1,65,128.2,276,517,1075]*1024;
RxBytes_non =zeros(8,length(BitRate));
Delay_non =zeros(8,length(BitRate));

RxBytes_aloha =zeros(8,length(BitRate));
Delay_aloha =zeros(8,length(BitRate));
RxBytes_p1 =zeros(8,length(BitRate));
Delay_p1 =zeros(8,length(BitRate));
RxBytes_p3 =zeros(8,length(BitRate));
Delay_p3 =zeros(8,length(BitRate));
RxBytes_p5 =zeros(8,length(BitRate));
Delay_p5 =zeros(8,length(BitRate));
%%
%p=0.7
a=16;
b=7;
RxBytes_non(a/2,b)=str2num(x_nonpersistant(b).Children(2).Children(a).Attributes(6).Value);
Delay_non(a/2,b)= str2num(regexprep(x_nonpersistant(b).Children(2).Children(a).Attributes(1).Value,'ns','','ignorecase'));
%%
for j=1:length(BitRate)
    for i = 2:2:16
RxBytes_non(i/2,j)= str2num(x_nonpersistant(j).Children(2).Children(i).Attributes(6).Value);
Delay_non(i/2,j)= str2num(regexprep(x_nonpersistant(j).Children(2).Children(i).Attributes(1).Value,'ns','','ignorecase'));

      % RxBytes_aloha(i/2,j)= str2num(x_aloha(j).Children(2).Children(i).Attributes(6).Value);
       % Delay_aloha(i/2,j)= str2num(regexprep(x_aloha(j).Children(2).Children(i).Attributes(1).Value,'ns','','ignorecase'));
 
    end
end 
%%

for j=1:length(BitRate)
    for i = 2:2:8
%RxBytes_p1(i/2,j)= str2num(x_p1(j).Children(2).Children(i).Attributes(6).Value);
 %       Delay_p1(i/2,j)= str2num(regexprep(x_p1(j).Children(2).Children(i).Attributes(1).Value,'ns','','ignorecase'));
		
        RxBytes_p3(i/2,j)= str2num(x_p3(j).Children(2).Children(i).Attributes(6).Value);
        Delay_p3(i/2,j)= str2num(regexprep(x_p3(j).Children(2).Children(i).Attributes(1).Value,'ns','','ignorecase'));

    end
end
%%
for j=1:length(BitRate)
    for i = 2:2:12
        RxBytes_p5(i/2,j)= str2num(x_p5(j).Children(2).Children(i).Attributes(6).Value);
        Delay_p5(i/2,j)= str2num(regexprep(x_p5(j).Children(2).Children(i).Attributes(1).Value,'ns','','ignorecase'));
		

    end
end
%% calc
Throughput_non= sum(RxBytes_non)*8/9;
Delay_non = sum(Delay_non)./Throughput_non;

Throughput_aloha = sum(RxBytes_aloha)*8/9;
Delay_aloha = sum(Delay_aloha)./Throughput_aloha;
Throughput_p1 = sum(RxBytes_p1)*8/9;
Delay_p1 = sum(Delay_p1)./Throughput_p1;
Throughput_p3 = sum(RxBytes_p3)*8/9;
Delay_p3 = sum(Delay_p3)./Throughput_p3;
%% plot
%through put
x=BitRate/1024;

plot(x,Throughput_non)

title('P=0.9-persistent Throughput for P-size=512')
xlabel('BitRate(Kbs)')
ylabel('ThroughPut(bps)')

%%
%delay
figure

plot(x,Delay_non);
title('P=0.9-persistent Delay for P-size=512')
xlabel('BitRate(Kbs)')
ylabel('Delay(ns)')
%%
figure
plot(Delay_non,Throughput_non);
title('ALOHA for P-size=512')
xlabel('ThroughPut(bps)')
ylabel('Delay(ns)')