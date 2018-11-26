image='map.JPG';
WAY_OF_LAP_CALC='LAPTIME';
% WAY_OF_LAP_CALC='GPS';

I=rgb2gray(imread(image));
% I=imresize(I,0.17);
threshold = 100;
Y=I>threshold;
B=strel('disk',6,8);
Y=imopen(Y,B);
Y=imerode(Y,B);
MAP=imcomplement(Y);
MAP=bwmorph(MAP,'skel',Inf);
temp=MAP;


K=[1 1 1;1 0 1;1 1 1];

B1=[1 1 0;
    0 1 0;
    0 0 0];

B2=[0 1 1;
    0 1 0;
    0 0 0];

B3=[0 0 1;
    0 1 1;
    0 0 0];

B4=[0 0 0;
    0 1 1;
    0 0 1];

B5=[0 0 0;
    0 1 0;
    0 1 1];

B6=[0 0 0;
    0 1 0;
    1 1 0];

B7=[0 0 0;
    1 1 0;
    1 0 0];

B8=[1 0 0;
    1 1 0;
    0 0 0];
for i=1:10
edges=((conv2(temp+0,K,'same').*(temp>0)) == 1);
while(max(max(edges)) ~= 0)
    temp=temp-edges;
    edges=((conv2(temp+0,K,'same').*(temp>0)) == 1);
end

temp=temp-bwhitmiss(temp,B1,imcomplement(B1));
temp=temp-bwhitmiss(temp,B2,imcomplement(B2));
temp=temp-bwhitmiss(temp,B3,imcomplement(B3));
temp=temp-bwhitmiss(temp,B4,imcomplement(B4));
temp=temp-bwhitmiss(temp,B5,imcomplement(B5));
temp=temp-bwhitmiss(temp,B6,imcomplement(B6));
temp=temp-bwhitmiss(temp,B7,imcomplement(B7));
temp=temp-bwhitmiss(temp,B8,imcomplement(B8));


end

temp=bwmorph(temp,'skel',Inf)+0;
MAP=(temp == 1);

tester=bwconncomp(MAP,8);
if(tester.NumObjects == 1)
    disp('SUCCES');
else
    disp('FAILED');
end


%% serialize map
MAP_SIZE=sum(sum(MAP));
%find random start
map_x=zeros(1,MAP_SIZE);
map_y=zeros(1,MAP_SIZE);

nx=size(MAP,1);
ny=size(MAP,2);
startx=-1;
starty=-1;
for i=1:nx
    for j=1:ny
        if(MAP(i,j) == 1)
            startx=i;
            starty=j;
            break;
        end
    end
    if(startx ~= -1)
        break
    end
end

if(strcmp(WAY_OF_LAP_CALC,'LAPTIME'))
    starty=2596;
    startx=1180;
end

nextx=startx+1;
nexty=starty;

map_x(1)=startx;
map_y(1)=starty;

count=2;

while(nextx ~= map_x(1) || nexty ~= map_y(1))
    map_x(count)=nextx;
    map_y(count)=nexty;
    
    for i=map_x(count)-1:map_x(count)+1
        for j=map_y(count)-1:map_y(count)+1
            if(MAP(i,j) && (i ~= map_x(count-1) || j ~= map_y(count-1)) && (i ~= map_x(count) || j ~= map_y(count)) )
                nextx=i;
                nexty=j;
            end
        end
    end
    nextx;
    nexty;
    if(count == MAP_SIZE)
        break;
    end
    count=count+1;
end

% map_x=(map_x-mean(map_x));
% map_y=(map_y-mean(map_y));

if(strcmp(WAY_OF_LAP_CALC,'GPS'))
[~,max_locs]=max(map_y);
max_loc=max_locs(1);

map_x=[map_x(max_loc:end) map_x(1:max_loc-1)];
map_y=[map_y(max_loc:end) map_y(1:max_loc-1)];

end
