use std::fs;
use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;

fn load_from_file(file_path: &str) -> Vec<i64>{
    let file = File::open(file_path).expect("file wasn't found.");
    let reader = BufReader::new(file);

    let numbers: Vec<i64> = reader
        .lines()
        .map(|line| line.unwrap().parse::<i64>().unwrap())
        .collect();
    return numbers;
}


fn input_file()  -> Vec<i64> {
    let filename = "/home/fbulow/proj/advent_of_code/2021/1/input";
    return load_from_file(filename)
}

fn solution_a()->i32{
    0
}
fn solution_b()->i32{
    0
}
    

fn the_truth() -> bool
{
    return true;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn solution_a(){
        assert_eq!(1529, solution_a());
    }
    // fn solution_b(){
    //     assert_eq!(1529, solution_b());
    // }
}
