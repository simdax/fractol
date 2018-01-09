#include "includes.h"

int	main(void)
{
  t_list	*list;
  char		*mots[5] = {"sali", "fsdfadf", "io", "ttrs", "truc de fou"};
  int i = 5;

  list = NULL;
  while (--i >= 0)
    ft_lstadd(&list,
	      ft_lstnew(mots[i], strlen(mots[i]))
	      );
  list = ft_lstsort(list, ft_cmp_strlen);
  ft_lstiter(list, ft_lstprint);
}
