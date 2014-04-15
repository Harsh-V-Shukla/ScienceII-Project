filename = 'rhinos.avi';
mov = VideoReader(filename);
opFolder = fullfile(cd, 'snaps');
if ~exist(opFolder, 'dir')
mkdir(opFolder);
end
numFrames = mov.NumberOfFrames;
numFramesWritten = 0;
for t = 1 : numFrames
currFrame = read(mov, t);    
opBaseFileName = sprintf('%3.3d.png', t);
opFullFileName = fullfile(opFolder, opBaseFileName);
imwrite(currFrame, opFullFileName, 'png');   
progIndication = sprintf('Wrote frame %4d of %d.', t, numFrames);
disp(progIndication);
numFramesWritten = numFramesWritten + 1;
end      
progIndication = sprintf('Wrote %d frames to folder "%s"',numFramesWritten, opFolder);
disp(progIndication);

