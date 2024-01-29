#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = reader(fd, buffer);
	line = cutter(buffer);
	buffer = update(buffer);
	if (!buffer)
		return (NULL);
	return (line);
}

char	*reader(int fd, char *buffer)
{
	char *tmp;
	int bytes;

	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!tmp)
		return(NULL);

	bytes = 1;
	while(!ft_strchr(buffer, '\n') && (bytes != 0)){

		bytes = read(fd, tmp, BUFFER_SIZE);
		if(bytes == -1){

			free(tmp);
			return(NULL);

		}
	tmp[bytes] = '\0';
	buffer = ft_strjoin(buffer, tmp);
	}
		free(tmp);
		return(buffer);
}

char	*cutter(char *buffer){

	size_t i;
	char *tmp;

	i = 0;
	while(buffer[i] != '\n' && buffer[i] != '\0'){
		i++;
	}

	tmp = malloc(sizeof(char) * (i + 2));

	if(!tmp)
		return(NULL);

	i = 0;
	while(buffer[i] != '\n' && buffer[i] != '\0'){

		tmp[i] = buffer[i];
		i++;

	}
	if(buffer[i] == '\n')
	{

		tmp[i] = buffer[i];
		i++;
	}
	tmp[i] = '\0';
	return(tmp);

}

char	*update(char *full_str)
{
	int		i;
	int		j;
	char	*restof;

	i = 0;
	while (full_str[i] && full_str[i] != '\n')
		i++;
	if (!full_str[i])
	{
		free(full_str);
		return (NULL);
	}
	restof = (char *)malloc(sizeof(char) * (ft_strlen(full_str) - i + 1));
	if (!restof)
		return (NULL);
	i++;
	j = 0;
	while (full_str[i])
		restof[j++] = full_str[i++];
	restof[j] = '\0';
	//These last two command lines looks like wrong. So, I might need to update these two lines in repo. I will review it in 02.06.2022
	free(full_str);
	return (restof);
}

int main(){

	int fd = open("test.txt", O_RDWR);

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));

}