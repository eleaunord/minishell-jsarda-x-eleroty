//valgrind --suppressions=valgrind_readline_leaks_ignore.supp ./minishell

// Tu incrémentes quand tu récupères tes variables env au début de ton programme. 
// Si tu lances ton minishell dans ton minishell tu vas récupérer la variable déjà incrémentée du minishell "parent". 
// Et tu vas incrémenter a nouveau. 
// Quand tu vas exit tu reviens sur l'env parent. Qui n'a eu qu'un +1.