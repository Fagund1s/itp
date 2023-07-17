# itp
projeto para conclusão de curso, esse programa foi elaborado para realizar processamento de imagens, na qual é usado representações de imagens através de bitmaps
O programa contem códigos de entrada na qual cada se refere a alguma função, sendo elas:

    gray: para criar uma nova imagem em escala de cinza;
    enlarge: para ampliar a imagem em 2x;
    reduce: para reduzir a imagem em 2x;
    rotate: para rotacionar a imagem em 90º no sentido anti-horário;

Comandos de entrada para execução no linux:

    ./main reduce < imgs/galinhos.ppm > imgs/reduce.ppm;
    ./main gray < imgs/galinhos.ppm > imgs/gray.ppmx;
    ./main enlarge < imgs/galinhos.ppm > imgs/enlarge.ppm
    ./main rotate < imgs/galinhos.ppm > imgs/rotate.ppm
