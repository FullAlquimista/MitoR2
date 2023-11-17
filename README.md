# Coletania de bibliotecas e aplicativos
A coletania MitoR2 é utilizada no aprendizado de programação
em C++.

## Bibliotecas utilizadas:
1. CopperSpice - Caso seja utilizado uma versão de compilador
   diferente dos binários pré-compilados. Recompile está biblioteca
   assim como qualquer outra biblioteca nesta lista.
   Para compilar com sucesso as seguintes bibliotecas dependentes
   devem também ser compiladas: openssl-1.1.1l, postgres-1x.x,
   ICU4c 6x.x.
2. PosgreSQL 1x.x - Especificamente a biblioteca libpq.dll e suas
   possíveis dependencias.
3. spdlog
4. nlohmann::json
5. GoogleTest.

### Usando GIT.
1. Instale a ferramenta e aplicativo: https://git-scm.com/
2. Vá ao serviços do windows e execute o serviço OpenSSH.
3. Na linha de comando execute o comando para criar uma chave
   privada e publica para acessar rápidamente e comitar no
   github. Execute: ssh-keygen e de coloque uma senha para
   está chave privada.
4. Execute o gerenciador de repositório com o comando:  ssh-agent -a
5. Para adicionar uma chave privada ao repositório execute:
   ssh-add .../id_rsa -> que é o nome do arquivo da sua chave
   privada.
6. Abra o arquivo da chave publica e copie todo o conteudo e
   adicione em SSH keys nas configurações de sua conta GitHub.

### Para criar um repositório apartir de um projeto:
1. Entre na pasta raiz do projeto e execute: git init.
2. .gitignore Crie este arquivo na pasta raiz para ignorar
   a adição de algum arquivo ou pasta ao repositório.
3. git branch -M "main" - Renomeia a branch atual para main.
4. Crie o repositório online no github com o mesmo nome da
   pasta raiz do projeto.
5. Link SSH: git@github.com:FullAlquimista/MitoR.git
   Link Https: https://github.com/FullAlquimista/MitoR.git
6. Cria o link entre o repositório local e o online com o
   comando: git remote add origem git@github.com:FullAlquimista/MitoR.git
7. Resumo:
   git init
   git add README.md
   git commit -m "first commit"
   git branch -M main
   git remote add origin git@github.com:FullAlquimista/MitoR.git
   git push -u origin main

### Comandos uteis
1. Após adicionar um arquivo ou diretório ao .gitignore que faz
   com que o git ignore certos arquivos e diretorios e não os
   mantenha no repositório e estes mesmos, já tinham sido 'empurrados'
   digite este comando para remove-los do repositório e não da
   pasta local do seu sistema.

git rm -r --cached "arquivo ou diretorio"