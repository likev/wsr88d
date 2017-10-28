const fs = require('fs');


//console.log('waiting...');

fs.readdir('./', (err, datedirs)=>{

	if (err) throw err;
	
	datedirs.sort();
	for(let datedir of datedirs){
		//console.log(datedir);
		if(/[0-9]{8}/.test(datedir)){
			//console.log(datedir);
			
			fs.mkdir('result-png/'+ datedir, (err, datedirs)=>{});
			fs.mkdir('result-png/'+ datedir + '/CR', (err, datedirs)=>{});
			fs.mkdir('result-png/'+ datedir + '/CR/37', (err, datedirs)=>{});
			
			let path = datedir + '/CR/37';
			fs.readdir(path, (err, files)=>{

				if (err) throw err;
				
				files.sort();
				for(let file of files){
					if(/^[0-9]{8}/.test(file)){
						console.log(path + '/' + file);
					}
				}
			});
		}
	}

})