% THIS IS A CASE DEPENDENT SCRIPT,
%YOU MAY NEED TO CHANGE THINGS.

% WAY_OF_LAP_CALC='GPS';
WAY_OF_LAP_CALC='LAPTIME';



%%read file
file='test_run3.csv';

scale=0.01785714 ;
data=csvread(file);
 if(strcmp(WAY_OF_LAP_CALC,'GPS'))
    x=data(:,1);
    y=data(:,2);
    Irms=scale*data(:,3);
 elseif(strcmp(WAY_OF_LAP_CALC,'LAPTIME'))
     if(strcmp(file,'race3_mapped.csv'))
%     race #3
    offset=450;
    LAPFILE='lap_times_race3.txt';
     elseif(strcmp(file,'test_run3.csv'))
%     test run #3
    offset=3040;
    LAPFILE='lap_times_test_run3.txt';
     elseif(strcmp(file,'race4_mapped.csv'))
%     race #4
    offset=425;
    LAPFILE='lap_times_race4.txt';
     end
    x=data(offset:end,1);
    y=data(offset:end,2);
    Irms=scale*data(offset:end,3);
 end

invalid= sum(x == 0);
x(1:invalid)=x(invalid+1);
y(1:invalid)=y(invalid+1);

N=size(x,1);
Fs=7.8;
Ts=1/Fs;
t=Ts/60*(1:N);

threshold = 20;
prin=Irms;
for i=2:N-1
    
    if (Irms(i) > threshold)
        Irms(i) = Irms(i-1);
    end
end
% plot(t,prin);
hold on
I_filt = fir(Irms);
% plot(t,I_filt);
% hold off
%% Fourier

I_mag=abs(fft(I_filt.*hann(N)))./N;
I_mag=I_mag(1:ceil((N+1)/2));
k=1:ceil((N+1)/2);
freq=Fs/N*k';
% plot(freq,I_mag);

%% Coordinate process
limit=200;
mask = x<limit;
xc=x.*mask;
yc=y.*mask;
for i=2:N-1
    if (xc(i)== 0)
        xc(i)=xc(i-1);
        yc(i)=yc(i-1);
    end
end
% plot(xc,yc);
points=zeros(1,N)-1;
counter=1;
xu_temp=zeros(1,N);
yu_temp=zeros(1,N);
k=2;
xu_temp(1)=xc(1);
yu_temp(1)=yc(1);
for i=2:N
    if(xc(i) ~= xc(i-1) || yc(i) ~= yc(i-1));
        points(k-1)=i;
        counter=1;
        xu_temp(k)=xc(i);
        yu_temp(k)=yc(i);
        k=k+1;
    else
        counter=counter+1;
    end
end
points=[1 points];
points = points(1:sum(points>0));


xu=xu_temp(1:sum(xu_temp>0));
yu=yu_temp(1:sum(yu_temp>0));

points=points(1:sum(points>0));

 mx=mean(xu);
 my=mean(yu);
 
 xu=xu-mx;
 yu=yu-my;
 
 xmax=max(xu);
 ymax=max(yu);
 xu=xu./xmax;
 yu=yu./ymax;
 
 %interpolate
x_int=zeros(1,N);
y_int=zeros(1,N);
for i=1:size(points,2)-1
    x_int(points(i):points(i+1)-1)=linspace(xu(i),xu(i+1),points(i+1)-points(i));
    y_int(points(i):points(i+1)-1)=linspace(yu(i),yu(i+1),points(i+1)-points(i));
end
 %find round boundaries
 if(strcmp(WAY_OF_LAP_CALC,'GPS'))
    [~,round]=findpeaks(x_int);
    round=[1 round];
 elseif(strcmp(WAY_OF_LAP_CALC,'LAPTIME'))
    lap_time=dlmread(LAPFILE,':');
    lap_time=lap_time(:,2:3);
    round=floor((lap_time(:,1)*60+lap_time(:,2))*Fs);
    round=[1 round'];
	round=cumsum(round);
 end


%average Irms per round
Iavg_round=zeros(1,size(round,2));
for i=1:size(round,2)-1
    Iavg_round(i)=mean(I_filt(round(i):round(i+1)-1));
end
Iavg_round(end)=mean(I_filt(round(end):end));


%fit Irms to MAP (adults only)
MAP_SIZE=sum(sum(MAP));
I_int=zeros(size(round,2),MAP_SIZE);
t_int=zeros(size(round,2),MAP_SIZE);
for i=1:size(round,2)-1
    tnew=linspace(t(round(i)), t(round(i+1)-1), MAP_SIZE);
    I_int(i,:)=interp1(t(round(i):round(i+1)-1),I_filt(round(i):round(i+1)-1),tnew);
    t_int(i,:)=tnew;
end
    tnew=linspace(t(round(end)), t(end), MAP_SIZE);
    I_int(end,:)=interp1(t(round(end):end),I_filt(round(end):end),tnew);
    t_int(end,:)=tnew;
tnew=linspace(0,t(end),sum(sum(MAP)));
I_int(end,:)=interp1(t,I_filt,tnew);

hold on
for i=1:size(round,2)-2
% figure
plot3(map_x,map_y,I_int(i,:));
grid;
title(Iavg_round(i))
end
% figure        
plot3(map_x,map_y,I_int(i,:));
title(Iavg_round(end));
grid;

Iglobal=mean(I_int,1);
