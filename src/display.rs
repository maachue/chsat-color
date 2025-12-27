use anyhow::Result;

use crate::{colors::unified::AnsiPaletteHex, utils::DOING_WORK_MSG};

pub fn json_dump(ansi: &AnsiPaletteHex) -> Result<()> {
    let temp_colors = ansi.read_as_indexmap();
    let json = serde_json::to_string_pretty(&temp_colors)?;

    eprintln!("{} json", DOING_WORK_MSG.style("   Dumping"));
    eprintln!("{} json dumping", DOING_WORK_MSG.style("    Finished"));

    println!("{}", json);

    Ok(())
}
