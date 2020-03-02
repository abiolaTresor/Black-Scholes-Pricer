# Black-Scholes

Ce projet à été effectué avec Abiola Trésor Djigui dans le cadre de l'UE (Unité d'enseignement) PAP (programmation avancée et projet) au troisième semestre de l'ENSIIE (École nationale supérieure d'informatique pour l'industrie et l'entreprise).

Le sujet "projet_2_black_scholes.pdf" et le rapport "rapport_du_projet.pdf" permettent de mieux comprendre l'utilité des autres fichiers présents.


Un bref aperçu du sujet :


En 1973, Fischer Black et Myron Scholes ont développé un modèle pour calculer le prix d’une option, dite européenne , liant le prix de cette option aux variations de l’actif sous-jacent (que l’on peut considérer comme une action).

$\frac{\partial C}{\partial t}+r S \frac{\partial C}{\partial S}+\frac{1}{2} \sigma^{2} S^{2} \frac{\partial^{2} C}{\partial S^{2}}=r C \quad \text { sur }[0, T] \times[0, L]$
$\frac{\partial \tilde{C}}{\partial \tilde{t}}=\mu \frac{\partial^{2} \tilde{C}}{\partial \tilde{s}^{2}}$

(équations utilisant les formules d'Ito et Black-Scholes)

Ecrire un programme C++ qui résoud (1) et (5) de manière structurée  , sans l’aide de bibliothèque extérieure. On utilisera une classe abstraite pour gérer les deux payoff considérés ci-dessus.
