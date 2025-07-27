find . -not -name "CMakeCXXCompilerId.cpp"  -regex '.*\.cpp$' -or -regex '.*\.hpp$'

rsync --port 2222 -avz --exclude '.git*' --exclude 'tests/' --exclude 'build/'  . localhost:~/ncvm-ui/

still nothing working right. did copy manually
