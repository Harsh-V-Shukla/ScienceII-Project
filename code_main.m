img=imread('2273.png');
img=rgb2gray(img);
s=size(img);
a=round(s(1)/2);
for i=1:a
      img1(i,:)=img(i,:);
end
for i=a:s(1)
      img2(i,:)=img(i,:);
end
% imshow(img1)
% imshow(img2)
% imshow(img);
s=size(img);
for i=1:s(1)
    for j=1:s(2)
        if(img(i,j)<180)
            img(i,j)=255;
        end
    end
end

imshow(img);
for i=1:s(1)
    for j=1:s(2)
        if(img(i,j)~=255)
            img(i,j)=0;
        end
    end
end


se=strel('square',2);
img=imerode(img,se);
img=imerode(img,se);
img=imdilate(img,se);
imshow(img)
BW = edge(img,'canny');

imshow(img)
%subplot(2,1,1);


% %size(H)
% %sum=zeros(500);
% % for i=1:360
% %     for j=1:3100
% %         sum(i)=sum(i)+H(j,i);
% %     end
% % end
% 
% %plot(sum);
% [H,T,R] = hough(BW,'RhoResolution',0.5,'Theta',-90:0.1:89.5);
% P = houghpeaks(H,1,'threshold',ceil(0.3*max(H(:))));
% imshow(H,[],'XData',T,'YData',R,'InitialMagnification','fit');
%        xlabel('\theta'), ylabel('\rho');
%        axis on, axis normal, hold on;
%            plot(T(P(:,2)),R(P(:,1)),'s','color','white');
% T(P(:,2))
% %Display the Hough matrix.
% subplot(2,1,2);
% imshow(imadjust(mat2gray(H)),'XData',T,'YData',R,...
%       'InitialMagnification','fit');
% title('Hough Transform of Gantrycrane Image');
% xlabel('\theta'), ylabel('\rho');
% axis on, axis normal, hold on;
% colormap(hot);
% 
% 
% s=size(img2);
% for i=1:s(1)
%     for j=1:s(2)
%         if(img2(i,j)<180)
%             img2(i,j)=255;
%         end
%     end
% end
% imshow(img2);
% for i=1:s(1)
%     for j=1:s(2)
%         if(img2(i,j)~=255)
%             img2(i,j)=0;
%         end
%     end
% end
% imshow(img2)
% se=strel('square',3);
% img2=imerode(img2,se);
% imshow(img2);
% 
% img2=imdilate(img2,se);
% 
% 
% BW = edge(img2,'canny');
% subplot(2,1,1);
% 
% title('Gantrycrane Image');
% size(H)
% 
% [H,T,R] = hough(BW,'RhoResolution',0.5,'Theta',-90:0.1:89.5);
% P = houghpeaks(H,1,'threshold',ceil(0.3*max(H(:))));
% imshow(H,[],'XData',T,'YData',R,'InitialMagnification','fit');
%        xlabel('\theta'), ylabel('\rho');
%        axis on, axis normal, hold on;
%            plot(T(P(:,2)),R(P(:,1)),'s','color','white');
% T(P(:,2))
% %Display the Hough matrix.
% subplot(2,1,2);
% imshow(imadjust(mat2gray(H)),'XData',T,'YData',R,...
%       'InitialMagnification','fit');
% title('Hough Transform of Gantrycrane Image');
% xlabel('\theta'), ylabel('\rho');
% axis on, axis normal, hold on;
% colormap(hot);
% 
% 
