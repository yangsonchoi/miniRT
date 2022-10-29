#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1920
# define HEIGHT 1080

typedef	struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef union u_color
{
	unsigned int	color;
	unsigned char	trgb[4];
}	t_color;

typedef struct s_ambient
{
	double	r;
	t_color	c;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	p;
	t_vec3	o;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	p;
	double	b;
	t_color	c;
}	t_light;

typedef struct s_sphere
{
	t_vec3	p;
	double	r;
	t_color	c;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	p;
	t_vec3	o;
	t_color	c;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	p;
	t_vec3	o;
	double	r;
	double	h;
	t_color	c;
}	t_cylinder;

typedef struct s_cnt
{
	int		al_cnt;
	int		c_cnt;
	int		l_cnt;
	int		sp_cnt;
	int		pl_cnt;
	int		cy_cnt;
}	t_cnt;

typedef struct s_descr
{
	t_cnt		cnt;
	t_ambient	al;
	t_camera	c;
	t_light		l;
	t_sphere	**sp;
	t_plane		**pl;
	t_cylinder	**cy;
}	t_descr;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

#endif