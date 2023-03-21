# EMDBResolutionSampling
Change Emdb sit file resoultion by voxel size  
  
## Requirement file
* EMDB sit file(PDB file converted by pdb_to_xyz)
* format : emd_(EMDB_Number).sit

## Input
* Target data EMDB number
* row, col, height
* step_size(Resoultion size)
  - 1 : default, 2: half, 3 : divided by 3 .. 9

## Output
* Sit file with changed resolution
