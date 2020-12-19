cd C:\Users\smfumagalli\Documents\Courses\Sass\server

Start-Process powershell -ArgumentList "tsc -w --allowSyntheticDefaultImports"
Start-Process powershell -ArgumentList "nodemon ./public/server.js"
"npm run sass"