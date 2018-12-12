const util = require('util');
const fs = require('fs');

const mkdir = util.promisify(fs.mkdir);
const readdir = util.promisify(fs.readdir);

//console.log('waiting...');

let print_dir = async ()=>{

	let datedirs = await readdir('./');
	datedirs.sort();	
	
	for(let datedir of datedirs){
		//console.log(datedir);
		if(/[0-9]{8}/.test(datedir)){
			//console.log(datedir);
			
			try{
				await mkdir('result-png/'+ datedir);
				await mkdir('result-png/'+ datedir + '/CR');
				await mkdir('result-png/'+ datedir + '/CR/37');
			}catch(error){
			
			}
			
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
}

print_dir();