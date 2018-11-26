%Draw a visualisation of RMS currents with respect to
%map position

figure
% ROUND=1;
for j=1:size(round,2)-1
% choose ROUND
ROUND=j;
close all



subplot(2,1,2);
axis([0 MAP_SIZE 0 15]);
title(Iavg_round(ROUND));
grid;
an=animatedline('Color','b','LineWidth',2.5);

subplot(2,1,1);
plot(map_y,-map_x,'LineWidth',2,'Color','black');



grid;
hold on;

plot(map_y(1),-map_x(1),'>','MarkerSize',7,...
    'MarkerEdgeColor','b',...
    'MarkerFaceColor',[0 1 0]);

p = plot(map_y(1),-map_x(1),'o','MarkerFaceColor','r');

F(1)=getframe(gcf);
for i=2:10:MAP_SIZE
    p.XData=map_y(i);
    p.YData=-map_x(i);

    addpoints(an,i,I_int(ROUND,i));
    F(i)=getframe(gcf);
    drawnow

end

end
%%
% create the video writer with 1 fps
  mywriterObj = VideoWriter('myVideo.avi');
  mywriterObj.FrameRate = 35;
  % set the seconds per image
% open the video writer
open(mywriterObj);
% write the frames to the video
for i=1:length(F)
    % convert the image to a frame
    frame = F(i).cdata ;    
    writeVideo(mywriterObj, frame);
end
% close the writer object
close(mywriterObj);