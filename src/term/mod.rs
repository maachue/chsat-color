use anyhow::Result;

use crate::colors::unified::AnsiPaletteHex;

#[cfg(target_family = "unix")]
mod unix;

pub fn apply(ansi: &AnsiPaletteHex) -> Result<()> {
    #[cfg(target_family = "unix")]
    unix::unix_term(ansi)?;
    Ok(())
}