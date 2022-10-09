#include "minishell.h"
#define CheckOprtr(c) ((ft_strichr(STRG_OPERATOR, (c)) == -1) ? 0 : 1)
#define CheckQuote(c) (((c) != CHAR_SGL_QUOTE && (c) != CHAR_DBL_QUOTE) ? 0 : (c))
#define CheckBlank(c) (((c) != CHAR_H_TAB && (c) != CHAR_V_TAB && (c) != CHAR_SPACE) ? 0 : 1)

static int	tk_isoprtr(const char *operator, size_t size)
{
	if (!CheckOprtr(operator[size]))
		return (0);
	if (!ft_strncmp(STRG_DLESS, operator, size + 1)
		|| !ft_strncmp(STRG_DGREAT, operator, size + 1))
		return (1);
	return (0);
}

int	tk_delimiter(const char *line, t_cmd *cmd, t_token *token)
{
	int				oprtr;
	int				quote;
	unsigned int	i;
	unsigned int	j;

	oprtr = 0;
	quote = 0;
	i = 0;
	j = i + 1;
	while (line[i])
	{
		if (i)
			token = lst_new();
		oprtr = CheckOprtr(line[i]);
		quote = CheckQuote(line[i]);
		j = i + 1;
		// 1. Si la fin de l'entrée est reconnue, le jeton courant doit être délimité.
		while (line[j])
		{
			/* Si le caractère précédent a été utilisé dans le cadre d'un opérateur
			et que le caractère actuel n'est pas entre guillemets
			et peut être utilisé avec les caractères actuels pour former un opérateur,
			il doit être utilisé dans le cadre de ce jeton (d'opérateur).*/
			if (oprtr && !quote && tk_isoprtr(line + i, j - i))
			{
				oprtr = CheckOprtr(line[j]);
				j++;
				continue ;
			}
			/* Si le caractère précédent a été utilisé dans le cadre d'un opérateur
			et que le caractère actuel ne peut pas être utilisé avec les caractères actuels pour former un opérateur,
			l'opérateur contenant le caractère précédent doit être délimité.*/
			else if (oprtr && !tk_isoprtr(line + i, j - i))
				break ;
			/* Si le caractère actuel est un guillemet simple ou un guillemet double
			et qu'il n'est pas entre guillemets,
			cela affectera les guillemets pour les caractères suivants jusqu'à la fin du texte entre guillemets.
			Le jeton de résultat doit contenir exactement les caractères qui apparaissent dans l'entrée (à l'exception de la jointure <newline>),
			non modifiés, y compris les guillemets incorporés ou englobants ou des opérateurs de substitution,
			entre le guillemet et la fin du texte cité. Le jeton ne doit pas être délimité par la fin du champ cité.*/
			else if (!quote && CheckQuote(line[j]))
				quote = line[j];
			else if (quote && line[j] == quote)
				quote = 0;
			/* Si le caractère actuel est un '$' sans guillemets, le shell doit identifier le début de tous les candidats à l'expansion des paramètres ( Parameter Expansion ), à la substitution de commande ( Command Substitution ) ou à l'expansion arithmétique ( Arithmetic Expansion ) à partir de leur introduction sans guillemets. séquences de caractères : '$' ou "${" , "$(" ou '`' , et "$((", respectivement. Le shell doit lire une entrée suffisante pour déterminer la fin de l'unité à développer (comme expliqué dans les sections citées). Lors du traitement des caractères, si des instances d'expansions ou de guillemets sont trouvées imbriquées dans la substitution, le shell les traitera de manière récursive de la manière spécifiée pour la construction trouvée. Les caractères trouvés depuis le début de la substitution jusqu'à sa fin, en tenant compte de toute récursivité nécessaire pour reconnaître les constructions imbriquées, doivent être inclus sans modification dans le jeton de résultat, y compris tout opérateur ou guillemet de substitution imbriqué ou englobant. Le jeton ne doit pas être délimité par la fin de la substitution.*/

			/* Si le caractère courant n'est pas entre guillemets
			et peut être utilisé comme premier caractère d'un nouvel opérateur,
			le jeton courant (le cas échéant) doit être délimité.
			Le caractère actuel doit être utilisé comme début du prochain jeton (opérateur).*/
			else if (!quote && CheckOprtr(line[j]))
				break ;
			/* Si le caractère courant est un <newline> sans guillemets, le jeton courant doit être délimité.*/

			/* Si le caractère courant est un <blank> sans guillemets,
			le jeton contenant le caractère précédent est délimité et le caractère courant doit être rejeté.*/
			else if (!quote && CheckBlank(line[j]))
				break ;
			/* Si le caractère précédent faisait partie d'un mot,
			le caractère courant doit être ajouté à ce mot.*/
			oprtr = CheckOprtr(line[j]);
			j++;
		}
// ft_printf("[%c] | oprtr = %i | quote = %i\n",line[j], oprtr, quote);
		if (quote)
			return (-1);
		token->s = ft_strndup(line + i, j - i);
		if (token != cmd->first)
			lst_add(cmd, cmd->last, token);
		while (line[j] && CheckBlank(line[j]))
			j++;
		i = j;
	}
	/* S'il n'y a pas de jeton courant,
	l'indicateur de fin d'entrée doit être renvoyé en tant que jeton.*/
	if (!i)
		token->s = ft_strdup("");
	return (0);
}
