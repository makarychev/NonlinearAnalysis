t0=0;
tf=1000
x0=[0.01 0.01 0.01];
interv= 0:.1:100;
handler = @ressler1;


outFile = fileread('Config.txt')
[t,x]=ode45(handler,interv,x0);
% comet3(x(:,1),x(:,2),x(:,3));
% plot3(x(:,1),x(:,2),x(:,3))
fileID = fopen(outFile, 'w+');
fprintf(fileID,'%6s %12s\n','x','exp(x)');
% fprinf(fileID, '%8s', 'asdasf');
fprintf(fileID,'%6.6f %6.6f %6.6f\n',x(:,1),x(:,2),x(:,3));
fclose(fileID);
riad_Y=x(:,2);

% plot(interv, riad_Y)
% tau=16
% step=0.2;
% tspan=t0:.01:tf;
% Y2=zeros(0,0);
% C =[];
% C1=[];
% C3=[];
% for n=2:10
% for i = 1:n  %знаходимо всі похідні ряди
% %   [t,X]=ode45(handler,tspan,x0, 1.e-6);
%  X=x(1+tau*(i-1):100000+tau*(i-1))
%  Kol_toch=size(X)
%  % for j=1:size(X)
%  %     Y1(j,i)=X(j,2);
%  % end;
%  if size(Y2) == 0
%      Y2=X(:,2);
%  else
%      Y3=[Y2, X(:,2);];
%      Y2=Y3;
%  end;
%  
%  x0=[X(tau+1,1) X(tau+1,2) X(tau+1,3)];
% end;
% end;
% 

% Y1=Y2;
% Y1=Y1';
% C =[];
% 
% for r=0:.1:8
%     c=0;
%     jj=1;
%     for i=1:length(Y1)-1
%         for j=i+1:length(Y1)
%             if i~=j 
%                 if (r-norm(Y2(i,:)-Y2(j,:)))>0 
%                     c=c+1;
%                 end;
%             end;
%         end;
%     end;
%     c=c/(length(Y1)^2);
%     C(end+1)=c;
%     
% end;
% if size(C1) == 0
%      C1=C(1,:);
%      C1=C1';
%  else
%      C3=[C1, C(1,:)';];
%      C1=C3;
%  end;
% 
% end;
% 
% %plot(log(C(:,2)).log(0:.1:4).'--rs',log(C(:,3)).log(0:.1:4).'-m',log(C(:,4)).log(0:.1:4).'--ok',log(C(:,5)).log(0:.1:4).'-+r',log(C(:,6)).log(0:.1:4).'--ok',log(C(:,7)).log(0:.1:4).'--ok',log(C(:,8)).log(0:.1:4).'--ok',log(C(:,9)).log(0:.1:4).'-m',log(C(:,4)).log(0:.1:4).'--rs');
% r=0:.1:8;
% for i=1:n-2
% plot(log(0:.1:8),log(C1(:,i)),'--rs');
% grid
% hold on % Эта команда позволяет
% end;
% %добавить график к уже существующем
% plot(log(0:.1:8),log(C1(:,n-1)),'-m');