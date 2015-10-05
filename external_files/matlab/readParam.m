function [a,b,c,filename] = readParam()
    fileID = fopen('input.txt', 'r+');
%     fscanf(fileID, '%4.4f\n', a);
%     fscanf(fileID, '%4.4f\n', b);
%     fscanf(fileID, '%4.4f\n', c);
%     fscanf(fileID, '%s', filename);
textread('input.txt', '%f %f %f %s', 1)
    fclose(fileID);
end
