/*
** mlx_mms.h for MinilibX in 
** 
** Made by Charlie Root
** Login   <ol@42.fr>
** 
** Started on  Mon Jul 31 16:37:50 2000 Charlie Root
** Last update Tue Oct 14 16:23:28 2019 Olivier Crouzet
*/

/*
**   MinilibX -  Please report bugs
*/


/*
**
** This library is a simple framework to help 42 students
** create simple graphical apps.
** It only provides the minimum functions, it's students' job
** to create the missing pieces for their own project :)
**
** The MinilibX can load XPM and PNG images.
** Please note that both image loaders are incomplete, some
** image may not load.
**
** For historical reasons, the alpha byte represent transparency
** instead of opacity.
** Also, for compatibility reasons, prototypes may show inconsistant
** types.
**
** Only the dynamic library is available. It must be placed in an appropriate path.
** ./ is one of them. You can also use DYLD_LIBRARY_PATH
**
*/


#ifndef MLX_MMS_H

#define	MLX_MMS_H

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

#endif /* MLX_H */
