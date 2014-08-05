%  SETPLOT2 sets user defined plotting parameters
%
%      User defined Matlab script for setting various Clawpack plotting
%      parameters.  This script is called by PLOTCLAW2.  A default
%      version of this script can be found in claw/matlab/setplot2.m and
%      copied to users working directory and modifed to set things up
%      differently.
%
%      Parameters that can be set with SETPLOT2
%
%        OutputFlag        - set to 'ascii' (default) to read ascii output
%                            or to 'hdf' to read hdf output files.
%        PlotType          - type of plot to produce:
% 			    - 1 = pcolor on slices (with optional contours)
% 			    - 2 = contour lines in 2d on white slices
% 			    - 3 = Schlieren plot on slices
% 			    - 4 = scatter plot of q vs. r
%
%        mq                  - which component of q to plot
%        UserVariable        - Set to 1 to specify a user defined variable.
%        UserVariableFile    - name of m-file mapping data to q
%        MappedGrid          - set to 1 if mapc2p.m exists for nonuniform
%                              grid
%        Manifold            - set to 1 if mapc2m.m exists for manifold plot.
%        MaxFrames           - max number of frames
%        MaxLevels           - max number of AMR levels
%        PlotData            - Data on refinement level k is plotted only if
%                              PlotData(k) == 1
%        PlotGrid            - PLot grid lines on level k is PlotGrid(k) /= 0
%        PlotGridEdges       - Plot 2d patch borders if PlotGridEdges(k) /= 0
%        ContourValues       - Set to desired contour values, or [] for no ...
% 	                       lines.
%        x0,y0               - center for scatter plots.
%        ScatterStyle        - symbols for scatter plot.
%        LineStyle           - same as ScatterStyle.
%        UserMap1d           - set to 1 if 'map1d' file exists.
%
%      All parameters can be modified by typing 'k' at the PLOTCLAW2 prompt.
%
%      See also PLOTCLAW2, SetPlotGrid, setPlotGridEdges.

OutputFlag = 'forestclaw';         % default value.
ForestClaw = 1;

PlotType = 1;                % type of plot to produce:
			     % 1 = pseudo-color (pcolor)
			     % 2 = contour
			     % 3 = Schlieren
			     % 4 = scatter plot of q vs. r

mq = 1;                      % which component of q to plot
UserVariable = 0;            % set to 1 to specify a user-defined variable
UserVariableFile = ' ';      % name of m-file mapping data to q
MappedGrid = 0;              % set to 1 if mapc2p.m exists for nonuniform grid
Manifold = 1;
MaxFrames = 1000;            % max number of frames to loop over
MaxLevels = 30;
MaskFlag = 0;
ReadBlockNumber = 1;
PlotData =  ones(1,MaxLevels);   % Data on refinement level k is plotted only if
			     % k'th component is nonzero
PlotGrid =  zeros(1,MaxLevels);   % Plot grid lines on each level?

PlotGridEdges = ones(1,MaxLevels);  % Plot edges of patches of each grid at
                                 % this level?

%---------------------------------

% Set to either a scalar, for automatic contours or a vector of contour levels.
ContourValues = [];

%---------------------------------

ShowUnderOverShoots = 0;
UseColorMapping = 'ParallelPartions';