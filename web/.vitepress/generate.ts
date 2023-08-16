import fs from "node:fs/promises";
import type { DefaultTheme } from "vitepress";

type Builder = (file: string, child: string) => string;

async function createMd(
  file: string,
  folder: string,
  sidebarItems: DefaultTheme.SidebarItem[],
  builder: Builder,
) {
  const tokens = file.split(".");
  const ext = tokens[tokens.length - 1];

  fs.writeFile(
    `web/${folder}/${file}.md`,
    builder(
      file,
      `
\`\`\`${ext == "hs" ? "haskell" : ext}
${(await fs.readFile(`${folder}/${file}`)).toString().trim()}
\`\`\`
`,
    ),
  );

  sidebarItems.push({
    text: file,
    link: `/${folder}/${file}`,
  });
}

async function writeFolder(folderName: string, builder: Builder) {
  const sidebarItems: DefaultTheme.SidebarItem[] = [];
  const files = (await fs.readdir(folderName)).filter((file) =>
    file.endsWith(".cpp"),
  );

  for (const file of files) {
    await createMd(file, folderName, sidebarItems, builder);
  }

  await fs.writeFile(
    `web/.vitepress/${folderName}.g.ts`,
    `
  export default ${JSON.stringify(sidebarItems)};
  `,
  );
}

writeFolder(
  "grader",
  (file, child) => `
# ${file}

${child}

See on [GitHub](https://github.com/Leomotors/2110211-intro-data-struct/blob/main/grader/${file})
`,
);
