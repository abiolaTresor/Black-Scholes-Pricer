# Black-Scholes

Ce projet à été effectué avec Abiola Trésor Djigui dans le cadre de l'UE (Unité d'enseignement) PAP (programmation avancée et projet) au troisième semestre de l'ENSIIE (École nationale supérieure d'informatique pour l'industrie et l'entreprise).

Le sujet "projet_2_black_scholes.pdf" et le rapport "rapport_du_projet.pdf" permettent de mieux comprendre l'utilité des autres fichiers présents.


Un bref aperçu du sujet :

$\frac{\partial C}{\partial t}+r S \frac{\partial C}{\partial S}+\frac{1}{2} \sigma^{2} S^{2} \frac{\partial^{2} C}{\partial S^{2}}=r C \quad \text { sur }[0, T] \times[0, L]$

$\frac{\partial \tilde{C}}{\partial \tilde{t}}=\mu \frac{\partial^{2} \tilde{C}}{\partial \tilde{s}^{2}}$

Ecrire un programme C++ qui résoud (1) et (5) de manière structurée, sans l’aide de bibliothèque extérieure. On utilisera une classe abstraite pour gérer les deux payoff considérés ci-dessus.
