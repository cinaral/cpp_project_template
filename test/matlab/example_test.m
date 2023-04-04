%** setup *%
test_name = 'example_test';
bin_fprefix = '../../build/bin';
bin_fname = append(test_name, '.exe');
fprefix = append('../../build/data/', test_name, '-');
ref_fprefix = append('../ref_data/', test_name, '-');
t_arr_fname = 't_arr.csv';
x_arr_fname = 'x_arr.csv';

is_drawing = true;
t_size = 1000;
x_dim = 3;
base_freq = 1.;

%** create reference data *%
ref_t_arr = linspace(0, 1, t_size).';
writematrix(ref_t_arr, append(ref_fprefix, t_arr_fname));  

ref_x_arr = zeros(t_size, x_dim);
for i = 1:t_size
	for j = 1:x_dim
		ref_x_arr(i, j) = sin(ref_t_arr(i)^j * 2 * pi * base_freq);
	end
end
writematrix(ref_x_arr, append(ref_fprefix, x_arr_fname));  
disp(append('Created reference data for ', test_name));

%** call the test binary *%
prev_pwd = pwd;
cd(bin_fprefix);
if isfile(bin_fname)
	if system(bin_fname) == 0
		disp(append(test_name, '	ok'));
	else 
		disp(append(test_name, '	fail'));
	end
else
	error(append(bin_fprefix, '/', bin_fname, ' does not exist. Use CMake to build the test.'));
end
cd(prev_pwd);

%** visualization *%
if is_drawing
	x_arr = readmatrix(append(fprefix, x_arr_fname));

	figure('Name', 'visualization');
	clf;
	hold on;
	plot(ref_t_arr, x_arr);
	plot(ref_t_arr, ref_x_arr, '--');
end
